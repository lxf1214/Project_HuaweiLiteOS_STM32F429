#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 LED_Task_Handle;
extern UINT32 Key_Task_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_LED_Task(void);
extern UINT32 Creat_Key_Task(void);
extern void LED_Task(void);
extern void Key_Task(void);

#endif


