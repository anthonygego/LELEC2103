#ifndef TERASIC_TOUCHPANEL_H_
#define TERASIC_TOUCHPANEL_H_
#include "alt_types.h"
typedef void *TOUCH_HANDLE;

#define TRUE 1
#define FALSE 0

////////////// configuration //////////////
#define X_RES   SCREEN_WIDTH
#define Y_RES   SCREEN_HEIGHT

#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	320

TOUCH_HANDLE Touch_Init(const alt_u32 spi_base, const alt_u32 penirq_base, const alt_u32 penirq_irq);
void Touch_UnInit(TOUCH_HANDLE pHandle);
int Touch_GetXY(TOUCH_HANDLE p, int *x, int *y);
void Touch_EmptyFifo(TOUCH_HANDLE pHandle);




typedef struct{
    int left;
    int right;
    int top;
    int bottom;
}RECT;

typedef struct{
    int x;
    int y;
}POINT;


int IsPtInRect(POINT *pt, RECT *rc);
void PtSet(POINT *pt, int x, int y);


#endif /*TERASIC_TOUCHPANEL_H_*/
