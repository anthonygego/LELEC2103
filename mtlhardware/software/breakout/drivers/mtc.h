#ifndef MULTI_TOUCH_H_
#define MULTI_TOUCH_H_

#include <alt_types.h>
#include "queue.h"

#define TOUCH_QUEUE_SIZE    		8

#define MTC_REG_CLEAR_FIFO      	0  // write only (write any value to clear fifo)
#define MTC_REG_INT_ACK         	1  // write only (write any value to ack)
#define MTC_REG_DATA_NUM        	2  // read only
#define MTC_REG_TOUCH_NUM       	3  // read only
#define MTC_REG_X1              	4  // read only
#define MTC_REG_Y1              	5  // read only
#define MTC_REG_X2              	6  // read only
#define MTC_REG_Y2              	7  // read only
#define MTC_REG_GESTURE         	8  // read only

// 8-way SingleTouch Pan
#define MTC_NO_GESTURE             	0x0
#define MTC_ST_NORTH                0x10
#define MTC_ST_N_EAST               0x12
#define MTC_ST_EAST                 0x14
#define MTC_ST_S_EAST               0x16
#define MTC_ST_SOUTH                0x18
#define MTC_ST_S_WEST               0x1A
#define MTC_ST_WEST                 0x1C
#define MTC_ST_N_WEST               0x1E

// SingleTouch Rotate
#define MTC_ST_ROTATE_CW            0x28
#define MTC_ST_ROTATE_CCW           0x29

// SingleTouch Click
#define MTC_ST_CLICK                0x20
#define MTC_ST_DOUBLECLICK          0x22

// 8-way MultiTouch Pan
#define MTC_MT_NORTH                0x30
#define MTC_MT_N_EAST               0x32
#define MTC_MT_EAST                 0x34
#define MTC_MT_S_EAST               0x36
#define MTC_MT_SOUTH                0x38
#define MTC_MT_S_WEST               0x3A
#define MTC_MT_WEST                 0x3C
#define MTC_MT_N_WEST               0x3E

// MultiTouch Zoom
#define MTC_ZOOM_IN                 0x48
#define MTC_ZOOM_OUT                0x49

// MultiTouch Click
#define MTC_MT_CLICK                0x40
#define MTC_1_POINT                 0x80
#define MTC_2_POINT                 0x81

typedef struct {
    alt_u32  TOUCH_BASE;
    alt_u32  INT_IRQ_NUM;
    alt_u32  INT_IRQ_CONTROLLER;
    queue   *pQueue;
} mtc_info;

typedef struct {
    alt_u8  event;
    alt_u8  touch_num;
    alt_u16 x1;
    alt_u16 y1;
    alt_u16 x2;
    alt_u16 y2;
} mtc_event;

mtc_info* mtc_init(alt_u32 MUTI_TOUCH_BASE, alt_u32 INT_IRQ_CONTROLLER, alt_u32 INT_IRQ_NUM);
void      mtc_uninit(mtc_info *p);
alt_u8    mtc_get_status(mtc_info *p, alt_u8 *Event, alt_u8 *TouchNum, alt_u16 *x1, alt_u16 *y1, alt_u16 *x2, alt_u16 *y2);
void      mtc_clear_event(mtc_info *p);

#endif /*MULTI_TOUCH_H_*/
