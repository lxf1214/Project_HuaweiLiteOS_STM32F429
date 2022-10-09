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

extern LITE_OS_SEC_BSS UINT8* m_aucSysMem0;

UINT32 Test_Task_Handle;
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
	
  uwRet = Creat_Test_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test_Task 任务创建失败!\n");
	}	
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
	
	printf("双向链表初始化中............\n");
	LOS_DL_LIST *head;                         //定义一个双向链表的头节点
	head = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST)); //动态申请头节点内存
	LOS_ListInit(head);                        //初始化双向链表
	if(!LOS_ListEmpty(head))                   //判断是否初始化成功
	{
		printf("双向链表初始化失败!\n");
	}
	else
	{
		printf("双向链表初始化成功!\n");
	}
	
	printf("添加节点和尾节点............\n");  //插入节点：顺序插入与从末尾插入
	
	//动态申请第一个节点的内容
	LOS_DL_LIST *node1 = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	//动态申请第二个节点的内容
	LOS_DL_LIST *node2 = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	//动态申请尾节点的内容
	LOS_DL_LIST *tail = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	
	printf("添加第一个节点与第二个节点............\n");
	LOS_ListAdd(head, node1);                   //添加第一个节点，连接在头节点上
	LOS_ListAdd(node1, node2);                  //添加第二个节点，连接在第一个节点上
	if((node1->pstPrev == head) && (node2->pstPrev == node1))  //判断是否插入成功
	{
		printf("添加节点成功!\n");
	}
	else
	{
		printf("添加节点失败!\n");
	}
	
	printf("将尾节点插入双向链表的末尾............\n");	
	LOS_ListTailInsert(head, tail);              //将尾节点插入双向链表的末尾
	if(tail->pstPrev == node2)                   //判断是否插入成功
	{
		printf("链表尾节点添加成功!\n");
	}
	else
	{
		printf("链表尾节点添加失败!\n");
	}	
	
	printf("删除节点............\n");	           //删除已有节点
  LOS_ListDelete(node1);	                     //删除第一个节点
	LOS_MemFree(m_aucSysMem0, node1);            //释放第一个节点的内存
	if(head->pstNext == node2)                   //判断是否删除成功
	{
		printf("删除节点成功!\n");
	}
	else
	{
		printf("删除节点失败!\n");
	}	
	
	while(1)
	{
		LED2_TOGGLE;
		printf("任务运行中!\n");
		LOS_TaskDelay(2000);
	}
}	

