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

/* 定义任务 ID 变量 */
UINT32 LED_Task_Handle;
UINT32 Key_Task_Handle;

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
	
	uwRet = Creat_LED_Task();
	if(uwRet != LOS_OK)
	{
		printf("LED_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Key_Task();
	if(uwRet != LOS_OK)
	{
		printf("Key_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_LED_Task 
* @ 功能说明 ：创建 LED_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_LED_Task(void)
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "LED_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LED_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&LED_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Key_Task 
* @ 功能说明 ：创建 Key_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Key_Task(void)
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Key_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：LED_Task 
* @ 功能说明 ：LED_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void LED_Task(void)
{
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LED2_TOGGLE;
		printf("LED 任务正在运行！\n");
		LOS_TaskDelay(1000);
  }
}	

/*******************************************************************************
* @ 函数名   ：Key_Task 
* @ 功能说明 ：Key_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Key_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		/* K1 被按下 */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			printf(" 挂起 LED 任务！ \n");
			uwRet = LOS_TaskSuspend(LED_Task_Handle);   /* 挂起 LED1 任务 */
			if(LOS_OK == uwRet)
			{
				printf(" 挂起 LED 任务成功！ \n");
			}
		}
		
		/* K2 被按下 */
		else if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			printf(" 恢复 LED 任务！ \n");
			uwRet = LOS_TaskResume(LED_Task_Handle);
			if(LOS_OK == uwRet)
			{
				printf(" 恢复 LED 任务成功！ \n");
			}
		}
		LOS_TaskDelay(20);        /* 20ms 扫描一次 */
  }
}		


