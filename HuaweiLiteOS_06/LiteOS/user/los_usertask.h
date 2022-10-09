#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_queue.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 Send_Task_Handle;
extern UINT32 Receive_Task_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_Send_Task(void);
extern UINT32 Creat_Receive_Task(void);
extern void Send_Task(void);
extern void Receive_Task(void);

#endif


