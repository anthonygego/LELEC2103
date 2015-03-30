#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>

#include "mtc.h"

static void mtc_query_data(mtc_info *p){
    
	// If data is available
    if (IORD(p->TOUCH_BASE, MTC_REG_DATA_NUM) > 0){

    	// Initialize event structure and load registers
    	mtc_event *pEvent = (mtc_event *) malloc(sizeof(mtc_event));
        pEvent->x1 = IORD(p->TOUCH_BASE, MTC_REG_X1);
        pEvent->y1 = IORD(p->TOUCH_BASE, MTC_REG_Y1);
        pEvent->x2 = IORD(p->TOUCH_BASE, MTC_REG_X2);
        pEvent->y2 = IORD(p->TOUCH_BASE, MTC_REG_Y2);
        pEvent->touch_num = IORD(p->TOUCH_BASE, MTC_REG_TOUCH_NUM);
        
        // Load gesture register
        alt_u8 gesture = IORD(p->TOUCH_BASE, MTC_REG_GESTURE);
        alt_u8 bValidEvnt = 1;

        // Find event type
        if (gesture == MTC_NO_GESTURE)
        {
            if (pEvent->touch_num  >= 1 && pEvent->touch_num  <= 2)
            	pEvent->event = (pEvent->touch_num  == 2) ? MTC_2_POINT : MTC_1_POINT;
            else
                bValidEvnt = 0;
        }
        else
        {
            if (gesture == 0xFF) // Filter the event
                bValidEvnt = 0;
            else
                pEvent->event = gesture;
        }
        
        // Insert event only if valid
        if (bValidEvnt)
        {
        	// If queue is full, remove the old one
            if (queue_is_full(p->pQueue))
            {
            	mtc_event *pOldEvent = (mtc_event *) queue_pop(p->pQueue);
                free(pOldEvent);
            }

            queue_push(p->pQueue, (alt_u32)pEvent);
        }
        else
        	free(pEvent);
    }        
}

static void mtc_isr(void* context){
    mtc_info *p = (mtc_info *)context;

    // Disable interrupts
    alt_ic_irq_disable(p->INT_IRQ_CONTROLLER, p->INT_IRQ_NUM);

	// Query data
	mtc_query_data(p);

	// Clear interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->TOUCH_BASE, 0x0);
	IOWR(p->TOUCH_BASE, MTC_REG_INT_ACK, 0x0);

	// Enable interrupts
	alt_ic_irq_enable(p->INT_IRQ_CONTROLLER, p->INT_IRQ_NUM);
}

mtc_info* mtc_init(alt_u32 MUTI_TOUCH_BASE, alt_u32 INT_IRQ_CONTROLLER, alt_u32 INT_IRQ_NUM){

	// Initializes peripheral info
	mtc_info *p = (mtc_info *) malloc(sizeof(mtc_info));
    p->TOUCH_BASE = MUTI_TOUCH_BASE;
    p->INT_IRQ_CONTROLLER = INT_IRQ_CONTROLLER;
    p->INT_IRQ_NUM = INT_IRQ_NUM;
    p->pQueue = queue_new(TOUCH_QUEUE_SIZE);
    
    // Enable interrupt
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(p->TOUCH_BASE,0x01);

    // Clear capture flag
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->TOUCH_BASE, 0x0);

    // register call-back function
    if (alt_ic_isr_register (p->INT_IRQ_CONTROLLER, p->INT_IRQ_NUM, mtc_isr, p, 0x0))
    {
        printf("failed to register touch irq\r\n");
        mtc_uninit(p);
        p = NULL;
    }

    return p;
}

void mtc_uninit(mtc_info *p){
    if(p)
    {
        queue_delete(p->pQueue);
        free(p);
    }
}

alt_u8 mtc_get_status(mtc_info *p, alt_u8 *event, alt_u8 *TouchNum, alt_u16 *x1, alt_u16 *y1, alt_u16 *x2, alt_u16 *y2 ){

	// If queue is empty, return 0
	if(queue_is_empty(p->pQueue))
		return 0;

	// Pop event on the queue and copy values
	mtc_event *pEvent = (mtc_event *) queue_pop(p->pQueue);
	*event = pEvent->event;
	*TouchNum = pEvent->touch_num;
	*x1 = pEvent->x1;
	*y1 = pEvent->y1;
	*x2 = pEvent->x2;
	*y2 = pEvent->y2;
	free(pEvent);

	return 1;
}

void mtc_clear_event(mtc_info *p){
    queue_empty(p->pQueue);
}
