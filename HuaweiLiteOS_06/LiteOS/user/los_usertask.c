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
UINT32 Receive_Task_Handle;
UINT32 Send_Task_Handle;

UINT32 Test_Queue_Handle;

/* 定义消息队列长度 */
#define TEST_QUEUE_LEN  16
#define TEST_QUEUE_SIZE 16

/* 全局变量声明 */
UINT32 send_data1 = 1;
UINT32 send_data2 = 2;

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
	
	/* 创建一个测试队列 */
  uwRet = LOS_QueueCreate("Test_Queue",                        /* 队列名称 */
	                       TEST_QUEUE_LEN,                       /* 队列长度 */
	                       &Test_Queue_Handle,                   /* 队列ID(句柄) */
	                       0,                                    /* 队列模式 */                         
	                       TEST_QUEUE_SIZE);	                   /* 节点大小，单位为1字节 */
	
	if(uwRet != LOS_OK)
	{
		printf("Test_Task 队列创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Receive_Task();
	if(uwRet != LOS_OK)
	{
		printf("Receive_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Send_Task();
	if(uwRet != LOS_OK)
	{
		printf("Send_Task 任务创建失败！失败代码 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_Receive_Task 
* @ 功能说明 ：创建 Receive_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Receive_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Receive_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Receive_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Receive_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Send_Task 
* @ 功能说明 ：创建 Send_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Send_Task()
{
	//定义一个创建任务的返回类型，初始化为创建成功的返回值
	UINT32 uwRet = LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Send_Task";         //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Send_Task;
	task_init_param.uwStackSize = 1024;            //栈大小
	
	uwRet = LOS_TaskCreate(&Send_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Receive_Task 
* @ 功能说明 ：Receive_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Receive_Task(void)
{
	UINT32 uwRet = LOS_OK;
	UINT32 *r_queue;
	UINT32 buffsize = 16;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		/* 队列读取，等待时间为一直等待 */
		uwRet = LOS_QueueRead(Test_Queue_Handle,             /* 读取队列ID(句柄) */
		                      &r_queue,                      /* 读取消息保存位置 */
		                      buffsize,                      /* 读取消息长度 */ 
		                      LOS_WAIT_FOREVER);             /* 等待时间:一直等 */
    
		if(LOS_OK == uwRet)
		{
			printf(" 本次读取到的消息是%d\n", *r_queue);
		}
		else
    {
			printf(" 消息读取出错，错误代码0x%X\n", uwRet);
		}
	}
}	

/*******************************************************************************
* @ 函数名   ：Send_Task 
* @ 功能说明 ：Send_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Send_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是一个无限循环，不能返回 */
	while(1)
	{
		/* K1 被按下 */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			/* 将消息写入到队列中，等待时间为 0 */
			uwRet = LOS_QueueWrite(Test_Queue_Handle,          /* 写入队列ID(句柄) */
			                       &send_data1,                /* 写入信息 */
			                       sizeof(send_data1),         /* 消息长度 */
														 0);   
			if(LOS_OK != uwRet)
			{
				printf(" 消息不能写入到消息队列！ 错误代码 0x%X\n",uwRet);
			}
		}
		
		/* K2 被按下 */
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			/* 将消息写入到队列中，等待时间为 0 */
			uwRet = LOS_QueueWrite(Test_Queue_Handle,          /* 写入队列ID(句柄) */
			                       &send_data2,                /* 写入信息 */
			                       sizeof(send_data2),         /* 消息长度 */
														 0);   
			if(LOS_OK != uwRet)
			{
				printf(" 消息不能写入到消息队列！ 错误代码 0x%X\n",uwRet);
			}
		}
		LOS_TaskDelay(20);        /* 20ms 扫描一次 */
  }
}		


