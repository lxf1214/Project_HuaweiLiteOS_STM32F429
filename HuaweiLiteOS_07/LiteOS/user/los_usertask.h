#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_sem.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 Read_Task_Handle;
extern UINT32 Write_Task_Handle;
extern UINT32 BinarySem_Handle;
extern uint8_t ucValue[2];

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_Read_Task(void);
extern UINT32 Creat_Write_Task(void);
extern void Read_Task(void);
extern void Write_Task(void);

#endif


