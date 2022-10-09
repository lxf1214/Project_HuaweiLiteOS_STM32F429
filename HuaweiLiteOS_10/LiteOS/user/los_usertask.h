#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_sem.h"
#include "los_sys.h"
#include "los_mux.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 HighPriority_Task_Handle;
extern UINT32 MidPriority_Task_Handle;
extern UINT32 LowPriority_Task_Handle;
extern UINT32 Mutex_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_HighPriority_Task(void);
extern UINT32 Creat_MidPriority_Task(void);
extern UINT32 Creat_LowPriority_Task(void);
extern void HighPriority_Task(void);
extern void MidPriority_Task(void);
extern void LowPriority_Task(void);

#endif


