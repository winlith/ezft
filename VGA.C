#include <i86.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "vga.h"
#include "types.h"

byte cursorStart, cursorEnd;
byte color;
static unsigned short far *screen;
static unsigned short screenOffset;

void vgaInit()
{
    screen = MK_FP(0xB800, 0);
    setPosition(0, 0);
    setColor(WHITE, BLACK);
}

void setColor(byte forecolor, byte backcolor)
{
    color = forecolor | (backcolor << 4);
}

void setPosition(byte x, byte y)
{
    screenOffset = y * 80 + x;
}

void setCursorPos(byte x, byte y)
{
    union REGS regs;
    regs.h.ah = 0x02;
    regs.h.bh = 0x00;
    regs.h.dl = x;
    regs.h.dh = y;
    int86(0x10, &regs, &regs);
}

void hideCursor()
{
    union REGS regs;
    regs.h.ah=0x03;
    regs.h.bh = 0x00;
    int86(0x10, &regs, &regs);
    cursorStart = regs.h.ch;
    cursorEnd = regs.h.cl;
    regs.h.ah = 0x01;
    regs.x.cx = 0x2000;
    int86(0x10, &regs, &regs);
}

void showCursor()
{
    union REGS regs;
    regs.h.ah = 0x01;
    regs.h.ch = cursorStart;
    regs.h.cl = cursorEnd;
    int86(0x10, &regs, &regs);
}

void drawChar(char character)
{
    screen[screenOffset] = (color << 8) | character;
    screenOffset++;
}

void drawString(byte x, byte y, char *string)
{
    byte linex = x;
    byte liney = y;
    int i;
    int len = strlen(string);
    setPosition(linex, liney);
    for (i = 0; i < len; i++)
    {
        if (string[i] == '\n')
        {
            liney++;
            setPosition(linex, liney);
        }
        else
        {
            screen[screenOffset] = (color << 8) | string[i];
            screenOffset++;
        }
    }
}

void debugPrint(char *format, ...)
{
    char msg[80];
    va_list va;
    va_start(va, format);
    vsnprintf(msg, 80, format, va);
    va_end(va);
    setColor(PINK, BLACK);
    drawString(0, 0, msg);
}

void drawBox(byte x, byte y, byte w, byte h)
{
    int i;

    setPosition(x, y);
    drawChar(0xC9);
    setPosition(x + w - 1, y);
    drawChar(0xBB);
    setPosition(x, y + h - 1);
    drawChar(0xC8);
    setPosition(x + w - 1, y + h - 1);
    drawChar(0xBC);
    for (i = 1; i < w - 1; i++)
    {
        setPosition(x + i, y);
        drawChar(0xCD);
        setPosition(x + i, y + h - 1);
        drawChar(0xCD);
    }
    for (i = 1; i < h - 1; i++)
    {
        setPosition(x, y + i);
        drawChar(0xBA);
        setPosition(x + w - 1, y + i);
        drawChar(0xBA);
    }
    fillRect(x + 1, y + 1, w - 2, h - 2);
}

void fillRect(byte x, byte y, byte w, byte h)
{
    int i, j;

    for (i = 0; i < h; i++)
    {
        setPosition(x, y + i);
        for (j = 0; j < w; j++)
        {
            drawChar(0x20);
        }
    }
}

void clearScreen()
{
    int i;

    for (i = 0; i < 80 * 25; i++)
    {
        screen[i] = (color << 8) | 0x20;
    }
}

void drawData(byte x, byte y, byte w, byte h, byte *data)
{
    int i, j;
    int k = 0;
    for (i = y; i < y + h; i++)
    {
        for (j = x; j < x + w; j++)
        {
            screen[i * 80 + j] = (data[k * 2 + 1] << 8) | data[k * 2];
            k++;
        }
    }
}

byte getVideoMode()
{
    union REGS regs;
    regs.h.ah = 0x0f; // read current video state
    int86(0x10, &regs, &regs);
    return regs.h.al;
}

void setVideoMode(byte mode)
{
    union REGS regs;
    regs.h.ah = 0x00; // set video mode
    regs.h.al = mode;
    int86(0x10, &regs, &regs);
}
