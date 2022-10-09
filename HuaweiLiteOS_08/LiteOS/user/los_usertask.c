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
UINT32 Pend_Task_Handle;
UINT32 Post_Task_Handle;

/* 定义二值信号的ID变量 */
UINT32 CountSem_Handle;


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
	
	/* 创建一个二值信号量 */
  uwRet = LOS_SemCreate(5,&CountSem_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("CountSem 创建失败！失败代码 0x%X\n",uwRet);
	}
	
	uwRet = Creat_Pend_Task();
	if(uwRet != LOS_OK)
	{
		printf("Pend_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Post_Task();
	if(uwRet != LOS_OK)
	{
		printf("Post_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_Pend_Task 
* @ 功能说明 ：创建 Pend_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Pend_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Pend_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Pend_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Pend_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Post_Task 
* @ 功能说明 ：创建 Post_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Post_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Post_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Post_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Post_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Pend_Task 
* @ 功能说明 ：Pend_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Pend_Task(void)
{
	UINT32 uwRet = LOS_OK;
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		if( Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			/* 获取一个计数信号量，等待时间为0 */
			uwRet = LOS_SemPend(CountSem_Handle,0);
			
			if(LOS_OK == uwRet)
			{
				printf("\r\nKEY1被按下，成功申请到停车位。\r\n");
			}
			else
			{
				printf("\r\nKEY1被按下，不好意思，现在停车场已满！\r\n");
			}				
		}
		LOS_TaskDelay(20);               //每20ms扫描一次
	}
}	

/*******************************************************************************
* @ 函数名   ：Post_Task 
* @ 功能说明 ：Post_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Post_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		if( Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			/* 释放一个计数信号量，LiteOS的计数信号量允许一直释放，在编程中注意一下即可 */
			uwRet = LOS_SemPost(CountSem_Handle);
			
			if(LOS_OK == uwRet)
			{
				printf("\r\nKEY2被按下，释放一个停车位。\r\n");
			}
			else
			{
				printf("\r\nKEY2被按下，但已无车位可以释放！\r\n");
			}				
		}
		LOS_TaskDelay(20);               //每20ms扫描一次
  }
}		


