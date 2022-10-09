/**
  ******************************************************************************
  * @file    los_task.c
  * @author  Lixf
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   Huawei_LiteOS
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板  
  *
  ******************************************************************************
  */

#include "los_usertask.h"

UINT32 TmrCb_Count1 = 0;
UINT32 TmrCb_Count2 = 0;

/* 定义任务 ID 变量 */
UINT16 Timer1_Handle;
UINT16 Timer2_Handle;

/*******************************************************************************
* @ 函数名   ：AppTaskCreat 
* @ 功能说明 ：任务创建，为了方便管理，所有的任务创建函数都可以放在这个函数里面
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 AppTaskCreat(void)
{
	/* 定义一个返回类型变量，初始化为 LOS_OK */
	UINT32 uwRet = LOS_OK;
	
  /* 创建一个软件定时器 */
	uwRet = LOS_SwtmrCreate(5000,                               //软件定时器定时时间
	                        LOS_SWTMR_MODE_ONCE,                //软件定时器模式 一次模式
	                        (SWTMR_PROC_FUNC)Timer1_Callback,   //软件定时器的回调函数
	                        &Timer1_Handle,                     //软件定时器 id
	                        0);
	if(uwRet != LOS_OK)
	{
		printf("软件定时器Timer1创建失败！\n");
		return uwRet;
	}
	
  /* 创建一个软件定时器 */
	uwRet = LOS_SwtmrCreate(1000,                               //软件定时器定时时间
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //软件定时器模式 一次模式
=======
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //软件定时器模式 一次模式
=======
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //软件定时器模式 一次模式
=======
	                        LOS_SWTMR_MODE_PERIOD,              //软件定时器模式 周期模式
>>>>>>> 3641d5e (鎻愪氦鏂囦欢)
>>>>>>> 917ff36 (鎻愪氦鏂囦欢)
>>>>>>> ead996f (鏇存柊鏂囦欢)
	                        (SWTMR_PROC_FUNC)Timer2_Callback,   //软件定时器的回调函数
	                        &Timer2_Handle,                     //软件定时器 id
	                        0);
	if(uwRet != LOS_OK)
	{
		printf("软件定时器Timer2创建失败！\n");
		return uwRet;
	}
	
	/* 启动一个软件定时器 */ 
	uwRet = LOS_SwtmrStart(Timer1_Handle);
	if(LOS_OK != uwRet)
	{
		printf("start Timer1 failed\n");
		return uwRet;
	}
	else
	{
		printf("start Timer1 sucess\n");
	}
		
	/* 启动一个软件定时器 */ 
	uwRet = LOS_SwtmrStart(Timer2_Handle);
	if(LOS_OK != uwRet)
	{
		printf("start Timer2 failed\n");
		return uwRet;
	}
	else
	{
		printf("start Timer2 sucess\n");
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Timer1_Callback 
* @ 功能说明 ：软件定时器回调函数1
* @ 参数     ：传入1个函数，但未使用
* @ 返回值   ：无
*******************************************************************************/
void Timer1_Callback(UINT32 reg)
{
	UINT32 tick_num1;
	
	TmrCb_Count1++;                                     //每回调一次加一
	LED1_TOGGLE;
	tick_num1 = (UINT32)LOS_TickCountGet();             //获取滴答定时器的计数值
	
	printf("Timer_CallBack_Count1 = %d\n", TmrCb_Count1);
	
	printf("tick_num1 = %d\n", tick_num1);
}	


/*******************************************************************************
* @ 函数名   ：Timer2_Callback 
* @ 功能说明 ：软件定时器回调函数2
* @ 参数     ：传入1个函数，但未使用
* @ 返回值   ：无
*******************************************************************************/
void Timer2_Callback(UINT32 arg)
{
	UINT32 tick_num2;

  TmrCb_Count2++;                                     //每回调一次加一
	LED2_TOGGLE;
	tick_num2 = (UINT32)LOS_TickCountGet();             //获取滴答定时器的计数值
	printf("Timer_CallBack2_Count2 = %d\n", TmrCb_Count2);
	
	printf("tick_num2 = %d\n", tick_num2);
}		

