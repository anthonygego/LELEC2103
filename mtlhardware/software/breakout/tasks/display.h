#ifndef DISPLAY_H_
#define DISPLAY_H_

#define ENABLE_ASYNC_TRANSFER

void display_task(void* pdata);
void display_isr(void * context);

#endif /* DISPLAY_H_ */
