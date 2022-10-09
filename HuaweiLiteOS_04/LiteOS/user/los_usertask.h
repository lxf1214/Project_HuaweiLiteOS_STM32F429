#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "./led/bsp_led.h"

extern UINT32 Test1_Task_Handle;
extern UINT32 Test2_Task_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_Test1_Task(void);
extern UINT32 Creat_Test2_Task(void);
extern void Test1_Task(void);
extern void Test2_Task(void);

#endif


