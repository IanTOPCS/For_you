# include "myDrawBigPoint.h"
# include "touch.h"
# include "lcd.h"
# include "key.h"
# include "led.h"
# include "delay.h"
# include "math.h"

gdIf gridInfo = {NULL, 0, 0, 0, 0, 0, 0};
u16 backGroundColor = BLACK, penColor = RED;
bool colorMode = false, drawFlag = false;

void initGridInfo(void) {
    u16 i, j;
    gridInfo.grid = malloc(lcddev.height * sizeof(bool*));
    for(i=0; i<lcddev.height; i++) {
        gridInfo.grid[i] = malloc(lcddev.width * sizeof(bool));
    }
    // set default value
    for(i=0; i<lcddev.height; i++) {
        for(j=0; j<lcddev.width; j++) {
            gridInfo.grid[i][j] = false;
        }
    }
    gridInfo.xl = lcddev.width;  
    gridInfo.yu = lcddev.height;
    gridInfo.xr = 0;
    gridInfo.yd = 0;
    return;
}

void destructor(void) {
    u16 i;
    for(i=0; i<lcddev.height; i++) {
        free (gridInfo.grid[i]);
    }
    free(gridInfo.grid);
    return;
}

// calculate color, consider colorMode
u16 calColor(u16 x, u16 y) {
    long cal;
    cal = ((y*(lcddev.width))+x);
    if (cal > (UINT16_MAX+1)) {
        cal = (UINT16_MAX)-(cal%(UINT16_MAX+1));
    }
    return (u16)cal;
}

void showAllColor(void) {
    u16 i, j;
    for(i=0; i<lcddev.height; i++) {
        for(j=0; j<lcddev.width; j++) {
            POINT_COLOR = calColor(j, i);
            LCD_DrawPoint(j, i);
        }
    }
    return;
}

// change color(mode 0: pen, 1: background)
void changeColor(bool mode) {
    u16 userChoose;
    // show all can use
    showAllColor();
    // choose by user
    while(1) {
        tp_dev.scan(0);
        if (tp_dev.sta&TP_PRES_DOWN) {
            if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                userChoose = calColor(tp_dev.x[0], tp_dev.y[0]);
                break;
            }
        }
    }
    // select by mode
    if (mode == true) {
        backGroundColor = userChoose;
    } else if (mode == false) {
        penColor = userChoose;
    }
    printGrid();
    return;
}

// flush all user-paint, reset as background-color
void clearPaint(void) {
    u16 i, j;
    // reset grid area
    for(i=0; i<lcddev.height; i++) {
        for(j=0; j<lcddev.width; j++) {
            gridInfo.grid[i][j] = false;
        }
    }
    // reset border spot
    gridInfo.xl = lcddev.width;  
    gridInfo.yu = lcddev.height;
    gridInfo.xr = 0;
    gridInfo.yd = 0;
    // reflush color to background-color
    LCD_Clear(backGroundColor);
    return;
}

void printGrid(void) {
    u16 i, j;
    // set background
    LCD_Clear(backGroundColor);
    // set user-paint
    for(i = 0; i<lcddev.height; i++) {
		for(j = 0; j<lcddev.width; j++) {
			if (gridInfo.grid[i][j] == true) {
                if (colorMode == true) {
                   POINT_COLOR = calColor(j, i);
                } else POINT_COLOR = penColor;
                LCD_DrawPoint(j, i);
			}
		}
	}
    return;
}

// true: in-LCD, false: out-of-LCD
bool borderDetect(u16 x, u16 y) {
    if (((s16)x<0)||((s16)x>=(lcddev.width))||((s16)y<0)||((s16)y>=(lcddev.height))) {
        return false;
    }
    return true;
}

void drawPointOnLCD(void) {
    // reset LCD screen
    printGrid();

    while(1) {
        tp_dev.scan(0);
        if (tp_dev.sta&TP_PRES_DOWN) {
            if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                gridInfo.grid[tp_dev.y[0]][tp_dev.x[0]] = true;
                if (colorMode == true) {
                   POINT_COLOR = calColor(tp_dev.x[0], tp_dev.y[0]);
                } else POINT_COLOR = penColor;
                LCD_DrawPoint(tp_dev.x[0], tp_dev.y[0]);
                break;
            }
        }
    }
    return;
}

void drawMyCircle(bool** arr, s16 fx, s16 fy, s16 radius) {
    int a, b, di;
    u16 x, y;
    a = 0, b = (u8)radius, di = (3-((u8)radius<<1));
    while(a<=b) {
        // 5
        x = fx+a, y = fy-b;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
        LCD_DrawPoint(x, y);
        arr[y][x] = true;

        // 0
        x = fx+b, y = fy-a;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
 		LCD_DrawPoint(x, y);
        arr[y][x] = true;

        // 4
        x = fx+b, y = fy+a;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
		LCD_DrawPoint(x, y);
        arr[y][x] = true;

        // 6
        x = fx+a, y = fy+b;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
		LCD_DrawPoint(x, y);
        arr[y][x] = true;

        // 1
        x = fx-a, y = fy+b;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
		LCD_DrawPoint(x, y);
        arr[y][x] = true;

        x = fx-b, y = fy+a;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
 		LCD_DrawPoint(x, y);
        arr[y][x] = true;

        // 2
        x = fx-a, y = fy-b;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
		LCD_DrawPoint(x, y);
        arr[y][x] = true;
        
        // 7
        x = fx-b, y = fy-a;
        if (colorMode == true) {
            POINT_COLOR = calColor(x, y);
        } else POINT_COLOR = penColor;
  		LCD_DrawPoint(x, y);
        arr[y][x] = true;
		a++;
		//使用Bresenham算法畫圓     
		if(di<0)di +=4*a+6;	  
		else {
			di+=10+4*(a-b);   
			b--;
		} 						
    }
    return;
}

void drawHaloCircle(void) {
    s16 distToRight, distToLeft, distToBottom, distToTop;
    s16 fx, fy, sx, sy, radius;
    u8 fontSize = 16;

    // reset LCD screen
    printGrid();

    // get first spot
    while(1) {
        tp_dev.scan(0);
        if (tp_dev.sta&TP_PRES_DOWN) {
            if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                fx = tp_dev.x[0], fy = tp_dev.y[0];
                LCD_ShowxNum(fx, fy, 1, 1, fontSize, 1);
                // for sure user finger out
                do {
                    tp_dev.scan(0);
                } while(tp_dev.sta&TP_PRES_DOWN);
                break;
            }
        }
    }

    // get second spot
    while(1) {
        tp_dev.scan(0);
        if (tp_dev.sta&TP_PRES_DOWN) {
            if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                sx = tp_dev.x[0], sy = tp_dev.y[0];
                LCD_ShowxNum(sx, sy, 2, 1, fontSize, 1);
                // for sure user finger out
                do {
                    tp_dev.scan(0);
                } while(tp_dev.sta&TP_PRES_DOWN);
                break;
            }
        }
    }

    // calculate radius
    radius = (s16)sqrt(pow((sx-fx), 2) + pow((sy-fy), 2));

    // border check
    distToRight = (lcddev.width - 1) - fx;
    distToLeft = fx;
    distToBottom = (lcddev.height - 1) - fy;
    distToTop = fy;
    if (radius > distToRight)  radius = distToRight;
    if (radius > distToLeft)   radius = distToLeft;
    if (radius > distToBottom) radius = distToBottom;
    if (radius > distToTop)    radius = distToTop;

    // draw circle with radius
    if (radius > 0) {
        drawMyCircle(gridInfo.grid, fx, fy, radius);
    }
    // show output
    printGrid();
    return;
}

void drawOnLCD(void) {
    drawFlag = true;
    // reset LCD screen
    printGrid();
    
    while(drawFlag == true) {
        // draw
        tp_dev.scan(0);
        if (tp_dev.sta&TP_PRES_DOWN) {
            if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                gridInfo.grid[tp_dev.y[0]][tp_dev.x[0]] = true;
                if (colorMode == true) {
                   POINT_COLOR = calColor(tp_dev.x[0], tp_dev.y[0]);
                } else POINT_COLOR = penColor;
                LCD_DrawPoint(tp_dev.x[0], tp_dev.y[0]);
            }
        }
    }
    return;
}

u16 calMin(u16 x, u16 y) {
    if (x<y) return x;
    return y;
}

u16 calMax(u16 x, u16 y) {
    if (x>y) return x;
    return y;
}

s16 calAbs(s16 x) {
    if (x<0) return -x;
    else return x;
}

void calBoundSpot(void) {
    u16 i, j;
    for(i=0; i<lcddev.height; i++) {
        for(j=0; j<lcddev.width; j++) {
            if (gridInfo.grid[i][j] == true) {
                // row detect
                gridInfo.xl = calMin(gridInfo.xl, j);
                gridInfo.xr = calMax(gridInfo.xr, j);
                // column detect
                gridInfo.yu = calMin(gridInfo.yu, i);
                gridInfo.yd = calMax(gridInfo.yd, i);
            }
        }
    }
    gridInfo.xmid = (gridInfo.xl + gridInfo.xr)/2;
    gridInfo.ymid = (gridInfo.yu + gridInfo.yd)/2;
    return;
}

void movePaint(bool mode) {
    u16 spotX, spotY;
    s16 diffx, diffy;
    s16 i, j;
    s16 yStart, yEnd, yStep;
    s16 xStart, xEnd, xStep;
    do {
        // get user-spot
        while(1) {
            tp_dev.scan(0);
            if (tp_dev.sta & TP_PRES_DOWN) {
                if (borderDetect(tp_dev.x[0], tp_dev.y[0]) == true) {
                    spotX = tp_dev.x[0]; 
                    spotY = tp_dev.y[0];
                    break;
                }
            }
        }
        // get border-spots
        calBoundSpot();
        // calculate difference between paint-mid and user-spot
        diffx = (s16)spotX - (s16)gridInfo.xmid;
        diffy = (s16)spotY - (s16)gridInfo.ymid;
        // border check, avoid out of border
        if (diffx < 0 && (s16)gridInfo.xl + diffx < 0) diffx = -(s16)gridInfo.xl;
        if (diffx > 0 && (s16)gridInfo.xr + diffx >= lcddev.width) diffx = (lcddev.width - 1) - gridInfo.xr;
        if (diffy < 0 && (s16)gridInfo.yu + diffy < 0) diffy = -(s16)gridInfo.yu;
        if (diffy > 0 && (s16)gridInfo.yd + diffy >= lcddev.height) diffy = (lcddev.height - 1) - gridInfo.yd;
        // scan direction, avoid cover output
        if (diffy > 0) { yStart = lcddev.height - 1; yEnd = -1; yStep = -1; }
        else { yStart = 0; yEnd = lcddev.height; yStep = 1; }
        if (diffx > 0) { xStart = lcddev.width - 1; xEnd = -1; xStep = -1; }
        else { xStart = 0; xEnd = lcddev.width; xStep = 1; }
        // move paint
        for (i = yStart; i != yEnd; i += yStep) {
            for (j = xStart; j != xEnd; j += xStep) {
                if (gridInfo.grid[i][j] == true) {
                    gridInfo.grid[i + diffy][j + diffx] = true;
                    if (diffy != 0 || diffx != 0) {
                        gridInfo.grid[i][j] = false;
                    }
                }
            }
        }
        // update new border-spot and mid
        gridInfo.xl += diffx;
        gridInfo.xr += diffx;
        gridInfo.yu += diffy;
        gridInfo.yd += diffy;
        gridInfo.xmid += diffx;
        gridInfo.ymid += diffy;
        // output new grid
        printGrid();
        // wait until user-finger
        if (mode == false) {
            do {
                tp_dev.scan(0);
            } while (tp_dev.sta & TP_PRES_DOWN);
        } else {
            tp_dev.scan(0);
        }
    } while((mode == true) && (tp_dev.sta & TP_PRES_DOWN));
    return;
}
