#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_sem.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 Pend_Task_Handle;
extern UINT32 Post_Task_Handle;
extern UINT32 CountSem_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_Pend_Task(void);
extern UINT32 Creat_Post_Task(void);
extern void Pend_Task(void);
extern void Post_Task(void);

#endif


