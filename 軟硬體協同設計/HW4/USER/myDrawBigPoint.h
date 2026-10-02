#ifndef __MYDRAWBIGPOINT__
#define __MYDRAWBIGPOINT__
# include "touch.h"
# include "stdbool.h"
# include "lcd.h"

typedef struct gdIf {
    bool **grid;
    u16 xl;
    u16 xr;
    u16 yu;
    u16 yd;
    u16 xmid;
    u16 ymid;
} gdIf;

extern gdIf gridInfo;
extern u16 backGroundColor, penColor;
// mode 0: user-choose, 1: colorful
extern bool colorMode, drawFlag;

// reset grid, clear LCD by background-color
void clearPaint(void);
// print grid(2-d bool array) on LCD
void printGrid(void);
// show a point on LCD, assigned by user
void drawPointOnLCD(void);
// show a halo circle by 2 spot on LCD
void drawHaloCircle(void);
// painting on LCD, press key-0 to break
void drawOnLCD(void);
// calculate colorful color with (x, y)
u16 calColor(u16 x, u16 y);
// show all color on LCD
void showAllColor(void);
// change color(mode 0: pen, 1: background)
void changeColor(bool mode);
// move paint from first to second spot assigned by user
void movePaint(bool);

// for coding, not for user
void initGridInfo(void);
void destructor(void);
// true: in-LCD, false: out-of-LCD
bool borderDetect(u16 x, u16 y);
// calculate border of user-painting
void calBoundSpot(void);
// draw circle and store in 2D array
void drawMyCircle(bool**, s16, s16, s16);
// calculate min
u16 calMin(u16 x, u16 y);
// calculate max
u16 calMax(u16 x, u16 y);
// calculate absolute
s16 calAbs(s16 x);

#endif
