#ifndef QUEUE_H_
#define QUEUE_H_

#include <includes.h>
#include <alt_types.h>

typedef struct
{
    alt_u32 num;
    alt_u32 front;
    alt_u32 rear;
    alt_u32 *data;
    OS_EVENT *sem;
} queue;

queue*   queue_new(int nqueueNum);
void     queue_delete(queue *pqueue);
alt_u8   queue_is_empty(queue *pqueue);
alt_u8   queue_is_full(queue *pqueue);
alt_u8   queue_push(queue *pqueue, alt_u32 data32);
alt_u32  queue_pop(queue *pqueue);
void     queue_empty(queue *pqueue);

#endif /*QUEUE_H_*/
