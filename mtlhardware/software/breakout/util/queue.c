#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

queue * queue_new(int nqueueNum){
    queue *pqueue = malloc(sizeof(queue));
    pqueue->front = 0;
    pqueue->rear = 0;
    pqueue->data = malloc(nqueueNum*sizeof(alt_u32));
    pqueue->num = nqueueNum;
    return pqueue;
}

void queue_delete(queue *pqueue){
	free(pqueue->data);
    free(pqueue);
}

alt_u8 queue_is_empty(queue *pqueue){
    return pqueue->front == pqueue->rear ? 1 : 0;
}

alt_u8 queue_is_full(queue *pqueue){
    return ((pqueue->front+1)%pqueue->num) == pqueue->rear ? 1 : 0;
}

alt_u8 queue_push(queue *pqueue, alt_u32 data32){
    if (queue_is_full(pqueue))
        return 0;

    pqueue->data[pqueue->front] = data32;
    pqueue->front = (pqueue->front+1)%pqueue->num;
    return 1;
}

alt_u32 queue_pop(queue *pqueue){
    if (queue_is_empty(pqueue))
        return 0;

    alt_u32 data32;
    data32 = pqueue->data[pqueue->rear];
    pqueue->rear = (pqueue->rear+1)%pqueue->num;
    return data32;
}

void queue_empty(queue *pqueue){
    pqueue->front = 0;
    pqueue->rear = 0;
}
