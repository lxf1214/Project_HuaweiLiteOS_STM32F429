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
UINT32 HighPriority_Task_Handle;
UINT32 MidPriority_Task_Handle;
UINT32 LowPriority_Task_Handle;

/* 定义二值信号的ID变量 */
UINT32 Mutex_Handle;


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
	
	/* 创建一个互斥量 */
  uwRet = LOS_MuxCreate(&Mutex_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("Mutex 创建失败！失败代码 0x%X\n",uwRet);
	}
	
	uwRet = Creat_HighPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("HighPriority_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_MidPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("MidPriority_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_LowPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("LowPriority_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_HighPriority_Task 
* @ 功能说明 ：创建 HighPriority_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_HighPriority_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 3;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "HighPriority_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)HighPriority_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&HighPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_MidPriority_Task 
* @ 功能说明 ：创建 MidPriority_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_MidPriority_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "MidPriority_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)MidPriority_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&MidPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_LowPriority_Task 
* @ 功能说明 ：创建 LowPriority_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_LowPriority_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "LowPriority_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LowPriority_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&LowPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：HighPriority_Task 
* @ 功能说明 ：HighPriority_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void HighPriority_Task(void)
{
	UINT32 uwRet = LOS_OK;
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		//获取二值信号量 BinarySem_Handle，没获取到则一直等待
		uwRet = LOS_MuxPend(Mutex_Handle, LOS_WAIT_FOREVER);
		
		if(uwRet == LOS_OK)
		{
			printf("HighPriority_Task Running!\n");
		}
		
		LED1_TOGGLE;
		LOS_MuxPost(Mutex_Handle);                 //释放二值信号量 BinarySem_Handle
		
		LOS_TaskDelay(1000);                           //延时1000Ticks
		
	}
}	

/*******************************************************************************
* @ 函数名   ：MidPriority_Task 
* @ 功能说明 ：MidPriority_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void MidPriority_Task(void)
{
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
    printf("MidPriority_Task Running！\n");
		LOS_TaskDelay(100);               //每100ms扫描一次
  }
}		

/*******************************************************************************
* @ 函数名   ：LowPriority_Task 
* @ 功能说明 ：LowPriority_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void LowPriority_Task(void)
{
	UINT32 uwRet = LOS_OK;
	static uint32_t i;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		//获取二值信号量 BinarySem_Handle，没获取到则一直等待
		uwRet = LOS_MuxPend(Mutex_Handle, LOS_WAIT_FOREVER);
		if(uwRet == LOS_OK)
		{
			printf("LowPriority_Task Running!\n");
		}
		
		LED2_TOGGLE;
		
		for(i=0; i<2000000; i++)
		{
			//模拟低优先级任务占用信号量
			//放弃剩余时间片，进行一次任务切换
			LOS_TaskYield();
		}
		
		printf("LowPriority_Task 释放互斥量！\r\n");
		LOS_MuxPost(Mutex_Handle);                 //释放二值信号量 BinarySem_Handle
		
		LOS_TaskDelay(1000);                           //延时1000Ticks
  }
}		

