#ifndef _LOS_USERTASK_H
#define _LOS_USERTASK_H

#include "los_task.ph"
#include "los_typedef.ph"
#include "los_sem.h"
#include "los_sys.h"
#include "los_mux.h"
#include "los_swtmr.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h"
#include "./usart/bsp_debug_usart.h"

extern UINT32 TmrCb_Count1;
extern UINT32 TmrCb_Count2;

extern UINT16 Timer1_Handle;
extern UINT16 Timer2_Handle;

extern UINT32 AppTaskCreat(void);
extern void Timer1_Callback(UINT32 arg);
extern void Timer2_Callback(UINT32 arg);

#endif


