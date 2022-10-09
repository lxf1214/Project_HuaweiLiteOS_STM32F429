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

UINT32 Test_Task_Handle;
//定义二值信号量
UINT32 BinarySem1_Handle;
UINT32 BinarySem2_Handle;

/*******************************************************************************
* @ 函数名   ：AppTaskCreat 
* @ 功能说明 ：任务创建，为了方便管理，所有的任务创建函数都可以放在这个函数里面
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void AppTaskCreat(void)
{
	UINTPTR uvIntSave;
	/* 定义一个返回类型变量，初始化为 LOS_OK */
	UINT32 uwRet = LOS_OK;
	
  uwRet = LOS_BinarySemCreate(0, &BinarySem1_Handle);
	if(uwRet != LOS_OK)
	{
		printf("BinarySem1_Handle 二值信号量创建失败!\n");
	}
	
	uwRet = LOS_BinarySemCreate(0, &BinarySem2_Handle);
	if(uwRet != LOS_OK)
	{
		printf("BinarySem2_Handle 二值信号量创建失败!\n");
	}
	
  uwRet = Creat_Test_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test_Task 任务创建失败!\n");
	}	
	
	uvIntSave = LOS_IntLock();                       //屏蔽所有中断
	
	//创建硬件中断，用于配置硬件中断并注册硬件中断处理功能
	LOS_HwiCreate(KEY1_INT_EXTI_IRQ,
	//平台的中断向量号，可以在 stm32fxxx.h 找得到，本例程由 bsp_exti.h 重新定义了
	              0,                    //硬件中断优先级
	              0,                    //硬件中断模式
	              KEY1_IRQHandler,      //中断服务函数
                0);                   //触发硬件中断时使用的中断处理程序的输入参数

	//创建硬件中断，用于配置硬件中断并注册硬件中断处理功能
	LOS_HwiCreate(KEY2_INT_EXTI_IRQ,
	//平台的中断向量号，可以在 stm32fxxx.h 找得到，本例程由 bsp_exti.h 重新定义了
	              0,                    //硬件中断优先级
	              0,                    //硬件中断模式
	              KEY2_IRQHandler,      //中断服务函数
                0);                   //触发硬件中断时使用的中断处理程序的输入参数
  
	LOS_IntRestore(uvIntSave);          //恢复所有中断
}

/*******************************************************************************
* @ 函数名   ：Creat_Test_Task 
* @ 功能说明 ：创建 Test_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Test_Task()
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;           //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Test_Task";      //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test_Task;
	task_init_param.uwStackSize = 1024;       //栈大小
	
	uwRet = LOS_TaskCreate(&Test_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Test_Task 
* @ 功能说明 ：在串口打印触发中断的信息
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Test_Task(void)
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是无限循环，不能返回 */
	while(1)
	{
		uwRet = LOS_SemPend(BinarySem1_Handle,0);
		if(uwRet == LOS_OK)
		{
			printf("触发中断的是 KEY1!\n");
		}//获取二值信号量，没获取则不等待
		
		uwRet = LOS_SemPend(BinarySem2_Handle,0);
		if(uwRet == LOS_OK)
		{
			printf("触发中断的是 KEY2!\n");
		}//获取二值信号量，没获取则不等待
		LOS_TaskDelay(20);
	}
}	

/*******************************************************************************
* @ 函数名   ：KEY1_IRQHandler 
* @ 功能说明 ：中断服务函数
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void KEY1_IRQHandler(void)
{
	//确保是否产生了 EXTI Line 中断
	if(EXTI_GetFlagStatus(KEY1_INT_EXTI_LINE) != RESET)
	{
		LOS_SemPost(BinarySem1_Handle);    //释放二值信号量 BinarySem1_Handle
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
	}
}		


/*******************************************************************************
* @ 函数名   ：KEY2_IRQHandler 
* @ 功能说明 ：中断服务函数
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void KEY2_IRQHandler(void)
{
	//确保是否产生了 EXTI Line 中断
	if(EXTI_GetFlagStatus(KEY2_INT_EXTI_LINE) != RESET)
	{
		LOS_SemPost(BinarySem2_Handle);    //释放二值信号量 BinarySem2_Handle
		//清除中断标志位
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
	}
}		





