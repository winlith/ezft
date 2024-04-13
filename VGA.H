#include "types.h"

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define WHITE 0x7
#define GRAY 0x8
#define BR_BLUE 0x9
#define BR_GREEN 0xa
#define BR_CYAN 0xb
#define BR_RED 0xc
#define PINK 0xd
#define YELLOW 0xe
#define BR_WHITE 0xf

void vgaInit();
void setColor(byte forecolor, byte backcolor);
void setColorRaw(byte rawColor);
void setPosition(byte x, byte y);
void setCursorPos(byte x, byte y);
void hideCursor();
void showCursor();
void drawChar(char character);
void drawString(byte x, byte y, char *string);
void drawBox(byte x, byte y, byte w, byte h);
void fillRect(byte x, byte y, byte w, byte h);
void clearScreen();
void drawData(byte x, byte y, byte w, byte h, byte *data);
byte getVideoMode();
void setVideoMode(byte mode);
