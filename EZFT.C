
#include <stdlib.h>
#include <stdio.h>
#include <i86.h>
#include <time.h>
#include "types.h"
#include "vga.h"

#define KEY_F2 0xbc
#define KEY_ESC 0x1b
#define KEY_ENTER 0x0d
#define KEY_BACKSP 0x08
#define KEY_UP 0xc8
#define KEY_DOWN 0xd0
#define KEY_LEFT 0xcb
#define KEY_RIGHT 0xcd

#define LOGO_WIDTH 50
#define LOGO_HEIGHT 7
byte logo[] = {
    ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01, 'Ü', 0x01,
    'Ü', 0x01, 'Ü', 0x01, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F,
    'Ü', 0x01, ' ', 0x11, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, 'ß', 0x01, ' ', 0x0F, ' ', 0x0F,
    ' ', 0x0F, 'Ü', 0x01, ' ', 0x11, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    'Ü', 0x1C, 'Ü', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'ß', 0x1C, ' ', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'ß', 0x01, ' ', 0x0F,
    ' ', 0x01, ' ', 0x01, 'Ü', 0x01, ' ', 0x11, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, ' ', 0x1C, ' ', 0x1C, 'Ü', 0x1C, 'Ü', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'ß', 0x1C, 'ß', 0x1C, ' ', 0x1C,
    ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'ß', 0x01,
    ' ', 0x0F, ' ', 0x0F, ' ', 0x01, 'Ü', 0x01, ' ', 0x11, 'Û', 0x1C,
    'Û', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'Ü', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'ß', 0x1C, 'ß', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    'ß', 0x01, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, 'Ü', 0x01, ' ', 0x11,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C, 'Û', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, 'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    'Û', 0x1C, 'Û', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C, ' ', 0x1C,
    ' ', 0x1C, 'ß', 0x01, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01, 'ß', 0x01,
    'ß', 0x01, 'ß', 0x01, 'ß', 0x01, ' ', 0x0F, ' ', 0x0F, ' ', 0x0F,
    ' ', 0x0F, ' ', 0x0F};

byte exitApp = false;
byte option = 4;
byte drive = 0;
byte tracks = 80;
byte heads = 2;
byte sectors = 18;

void generateData(byte *buffer)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        unsigned int r;
        byte l, h;
        r = rand();
        l = r;
        h = r >> 8;
        buffer[i * 2] = l;
        buffer[i * 2 + 1] = h;
    }
}

void resetDisk(byte drive)
{
    union REGS inregs, outregs;
    inregs.h.ah = 0;
    inregs.h.dl = drive;
    int86(0x13, &inregs, &outregs);

    if (outregs.x.cflag != 0)
    {
        printf("Error resetting drive %d", drive);
    }
}

byte readSector(byte track, byte head, byte sector, byte *buffer)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int attempts = 0;

    inregs.h.ah = 2; // read sectors
    inregs.h.al = 1; // read 1 sector
    inregs.h.dh = head;
    inregs.h.dl = 0; // drive a
    inregs.h.ch = track;
    inregs.h.cl = sector;
    inregs.x.bx = FP_OFF(buffer);
    segregs.es = FP_SEG(buffer);

    do
    {
        int86x(0x13, &inregs, &outregs, &segregs);
        attempts++;
    } while (outregs.x.cflag != 0 && attempts < 30);

    return outregs.h.ah;
}

byte writeSector(byte track, byte head, byte sector, byte *buffer)
{
    union REGS inregs, outregs;
    struct SREGS segregs;
    int attempts = 0;

    inregs.h.ah = 3; // write sectors
    inregs.h.al = 1; // write 1 sector
    inregs.h.dh = head;
    inregs.h.dl = 0; // drive a
    inregs.h.ch = track;
    inregs.h.cl = sector;
    inregs.x.bx = FP_OFF(buffer);
    segregs.es = FP_SEG(buffer);

    do
    {
        int86x(0x13, &inregs, &outregs, &segregs);
        attempts++;
    } while (outregs.x.cflag != 0 && attempts < 30);

    return outregs.h.ah;
}

byte waitForKey()
{
    union REGS inregs;
    union REGS outregs;

    inregs.h.ah = 0x0;
    int86(0x16, &inregs, &outregs);
    if (outregs.h.al == 0)
    {
        return outregs.h.ah + 0x80;
    }
    return outregs.h.al;
}

void editDrive()
{
    byte key;
    byte editing = true;

    setColor(BR_RED, BLACK);
    setCursorPos(43, 12);
    showCursor();
    while (editing)
    {
        setPosition(43, 12);
        key = waitForKey();
        switch (key)
        {
        case 'a':
        case 'A':
            drawChar('A');
            drive = 0;
            break;
        case 'b':
        case 'B':
            drawChar('B');
            drive = 1;
            break;
        case 'c':
        case 'C':
            drawChar('C');
            drive = 2;
            break;
        case 'd':
        case 'D':
            drawChar('D');
            drive = 3;
            break;
        case KEY_ENTER:
            editing = false;
            break;
        default:
            break;
        }
    }
    hideCursor();
}

void editSetting()
{
    byte *setting;
    char settingStr[3];
    byte newSetting;
    byte max, line, key;
    byte col = 43;
    byte colOff = 1;
    byte editing = true;

    switch (option)
    {
    case 1:
        setting = &tracks;
        max = 99;
        line = 13;
        break;
    case 2:
        setting = &heads;
        max = 2;
        line = 14;
        break;
    case 3:
        setting = &sectors;
        max = 99;
        line = 15;
        break;
    default:
        return;
    }

    itoa(*setting, settingStr, 10);
    if (*setting >= 10)
    {
        colOff = 2;
    }
    showCursor();
    setColor(BR_RED, BLACK);
    while (editing)
    {
        setCursorPos(col + colOff, line);
        key = waitForKey();
        if (key >= '0' && key <= '9')
        {
            if (colOff < 2)
            {
                setPosition(col + colOff, line);
                drawChar(key);
                settingStr[colOff] = key;
                colOff++;
            }
        }
        else if (key == KEY_BACKSP)
        {
            if (colOff > 0)
            {
                colOff--;
                setPosition(col + colOff, line);
                drawChar(' ');
                settingStr[colOff] = 0x0;
            }
        }
        else if (key == KEY_ENTER)
        {
            newSetting = atoi(settingStr);
            if (newSetting != 0 && newSetting <= max)
            {
                *setting = newSetting;
                editing = false;
            }
        }
    }
    hideCursor();
}

void runTest()
{
    byte key;
    byte confirming = true;
    byte testing = true;

    setColor(BR_WHITE, BLACK);
    fillRect(32, 11, 15, 9);
    setColor(BR_WHITE, RED);
    drawBox(16, 11, 48, 4);
    drawString(36, 11, "WARNING");
    drawString(17, 12, "All data on the floppy disk will be DESTROYED.");
    drawString(22, 13, "Press ESC to cancel, F2 to continue.");
    while (confirming)
    {
        key = waitForKey();
        switch (key)
        {
        case KEY_ESC:
            confirming = false;
            testing = false;
            break;
        case KEY_F2:
            confirming = false;
            break;
        default:
            break;
        }
    }

    if (testing)
    {
        byte exiting = false;
        unsigned int seed = time(NULL);
        byte *data = malloc(512 * sizeof(byte));
        byte *buffer = malloc(512 * sizeof(byte));
        char message[20];
        unsigned int totalSectors = tracks * heads * sectors;
        byte track, head, sector, progressPercent, progressBar;
        unsigned int progress = 0;
        unsigned int badSectors = 0;

        srand(seed);
        setColor(BR_WHITE, BLACK);
        drawBox(14, 11, 52, 9);
        drawBox(14, 19, 52, 3);
        setPosition(14, 19);
        drawChar('Ì');
        setPosition(65, 19);
        drawChar('¹');
        drawString(31, 11, "Testing in progress");
        drawString(36, 12, "Writing...");
        sprintf(message, "Track:   /%02d", tracks);
        drawString(35, 13, message);
        sprintf(message, "Head:  /%01d", heads);
        drawString(36, 14, message);
        sprintf(message, "Sector:   /%02d", sectors);
        drawString(34, 15, message);
        drawString(32, 16, "Progress:");
        drawString(29, 18, "Bad sectors:");

        waitForKey();

        // while (testing && progress < totalSectors)
        // {
        //     sector = (progress % sectors) + 1;
        //     head = (progress / sectors) % heads;
        //     track = (progress / sectors) / heads;
        //     progressPercent = progress / totalSectors * 100;
        //     progressBar = progressPercent/2;
        // }
    }

    setColor(BR_WHITE, BLACK);
    fillRect(14, 11, 52, 11);
}

void executeOption()
{
    switch (option)
    {
    case 0:
        editDrive();
        break;
    case 1:
    case 2:
    case 3:
        editSetting();
        break;
    case 4:
        runTest();
        break;
    case 5:
        exitApp = true;
        break;
    default:
        break;
    }
}

void displayBg()
{
    drawData((80 - LOGO_WIDTH) / 2, 1, LOGO_WIDTH, LOGO_HEIGHT, logo);
    setColor(BR_BLUE, BLACK);
    drawString(15, 8, "EZ Floppy Tester");
    setColor(GRAY, BLACK);
    drawString(1, 24, "v0.1");
    drawString(56, 24, "github.com/winlith/ezft");
}

void drawMenu()
{
    char driveLetter;
    char trackNum[3];
    char headNum[2];
    char sectorNum[3];

    driveLetter = drive + 0x41;
    itoa(tracks, trackNum, 10);
    itoa(heads, headNum, 10);
    itoa(sectors, sectorNum, 10);
    setColor(BR_WHITE, BLACK);
    drawBox(32, 11, 15, 9);

    if (option == 0)
        setColor(BR_RED, BLACK);
    drawString(36, 12, "Drive:");
    setPosition(43, 12);
    drawChar(driveLetter);
    setColor(BR_WHITE, BLACK);

    if (option == 1)
        setColor(BR_RED, BLACK);
    drawString(35, 13, "Tracks:");
    drawString(43, 13, trackNum);
    setColor(BR_WHITE, BLACK);

    if (option == 2)
        setColor(BR_RED, BLACK);
    drawString(36, 14, "Heads:");
    drawString(43, 14, headNum);
    setColor(BR_WHITE, BLACK);

    if (option == 3)
        setColor(BR_RED, BLACK);
    drawString(34, 15, "Sectors:");
    drawString(43, 15, sectorNum);
    setColor(BR_WHITE, BLACK);

    if (option == 4)
        setColor(BR_RED, BLACK);
    drawString(35, 17, "Start test");
    setColor(BR_WHITE, BLACK);

    if (option == 5)
        setColor(BR_RED, BLACK);
    drawString(38, 18, "Exit");
    setColor(BR_WHITE, BLACK);
}

void mainMenu()
{
    byte key;
    while (!exitApp)
    {
        drawMenu();
        key = waitForKey();
        switch (key)
        {
        case KEY_UP:
            if (option == 0)
                option = 5;
            else
                option--;
            break;
        case KEY_DOWN:
            option++;
            option %= 6;
            break;
        case KEY_ESC:
            option = 5;
            break;
        case KEY_ENTER:
            executeOption();
            break;
        }
    }
}

int main()
{
    byte oldmode;
    oldmode = getVideoMode();
    setVideoMode(0x03);
    vgaInit();
    hideCursor();
    displayBg();
    mainMenu();
    setVideoMode(oldmode);
    return 0;
}
