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


#define KEY1_EVENT (0x01 << 0) //设置事件掩码的位0
#define KEY2_EVENT (0x01 << 1) //设置事件掩码的位1

extern UINT32 LED_Task_Handle;
extern UINT32 Key_Task_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_LED_Task(void);
extern UINT32 Creat_Key_Task(void);
extern void LED_Task(void);
extern void Key_Task(void);


#endif


