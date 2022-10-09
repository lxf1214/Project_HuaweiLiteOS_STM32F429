#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_sem.h"
#include "los_sys.h"
#include "los_mux.h"
#include "los_swtmr.h"
#include "los_membox.h"
#include "los_memory.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"
#include "./exti/bsp_exti.h"


extern UINT32 Test_Task_Handle;
//定义二值信号量
extern UINT32 BinarySem1_Handle;
extern UINT32 BinarySem2_Handle;

extern void KEY1_IRQHandler(void);
extern void KEY2_IRQHandler(void);

extern void AppTaskCreat(void);
extern UINT32 Creat_Test_Task(void);
extern void Test_Task(void);


#endif


