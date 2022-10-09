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
UINT32 Read_Task_Handle;
UINT32 Write_Task_Handle;

/* 定义二值信号的ID变量 */
UINT32 BinarySem_Handle;
uint8_t ucValue[2] = {0x00, 0x00};

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
  uwRet = LOS_BinarySemCreate(1,&BinarySem_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("BinarySem 创建失败！失败代码 0x%X\n",uwRet);
	}
	
	uwRet = Creat_Read_Task();
	if(uwRet != LOS_OK)
	{
		printf("Read_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Write_Task();
	if(uwRet != LOS_OK)
	{
		printf("Write_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_Read_Task 
* @ 功能说明 ：创建 Read_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Read_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Read_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Read_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Write_Task 
* @ 功能说明 ：创建 Write_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Write_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Write_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Write_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Write_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Read_Task 
* @ 功能说明 ：Read_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Read_Task(void)
{
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LOS_SemPend(BinarySem_Handle, LOS_WAIT_FOREVER);
		//获取二值信号量 BinarySem_Handle, 没获取到则一直等待
		
		if(ucValue[0] == ucValue[1])
		{
			printf("\r\nSuccessful\r\n");
		}
		else
		{
			printf("\r\nFail\r\n");
		}
		LOS_SemPost(BinarySem_Handle);         //释放二值信号量 BinarySem_Handle
	}
}	

/*******************************************************************************
* @ 函数名   ：Write_Task 
* @ 功能说明 ：Write_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Write_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		LOS_SemPend(BinarySem_Handle, LOS_WAIT_FOREVER);
		//获取二值信号量 BinarySem_Handle, 没获取到则一直等待
		ucValue[0]++;
		LOS_TaskDelay(1000);             /* 延时1000Ticks */

		ucValue[1]++;
    LOS_SemPost(BinarySem_Handle);  //释放二值信号量 BinarySem_Handle	
    LOS_TaskYield();                //放弃剩余时间片，进行一次任务切换		
  }
}		


