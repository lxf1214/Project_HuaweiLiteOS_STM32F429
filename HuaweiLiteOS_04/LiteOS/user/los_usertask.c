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
UINT32 Test1_Task_Handle;
UINT32 Test2_Task_Handle;

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
	
	uwRet = Creat_Test1_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test1_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Test2_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test2_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_Test1_Task 
* @ 功能说明 ：创建 Test1_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Test1_Task(void)
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Test1_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test1_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Test1_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Test2_Task 
* @ 功能说明 ：创建 Test2_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Test2_Task(void)
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Test2_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test2_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Test2_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Test1_Task 
* @ 功能说明 ：Test1_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Test1_Task(void)
{
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LED2_TOGGLE;
		printf("任务 1 运行中, 每 1000ticks 打印一次信息\r\n");
		LOS_TaskDelay(1000);
  }
}	

/*******************************************************************************
* @ 函数名   ：Test1_Task 
* @ 功能说明 ：Test1_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Test2_Task(void)
{
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LED1_TOGGLE;
		printf("任务 2 运行中, 每 500ticks 打印一次信息\r\n");
		LOS_TaskDelay(500);
  }
}


