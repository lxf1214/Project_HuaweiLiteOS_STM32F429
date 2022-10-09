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

#define MALLOC_MEM_SIZE 16                        //分配内存的大小

extern UINT32 LED_Task_Handle;
extern UINT32 Key_Task_Handle;

extern UINT32 AppTaskCreat(void);
extern UINT32 Creat_LED_Task(void);
extern UINT32 Creat_Key_Task(void);

extern void LED_Task(void);
extern void Key_Task(void);

#endif


