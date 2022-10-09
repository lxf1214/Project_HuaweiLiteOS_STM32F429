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
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  *
  ******************************************************************************
  */

#include "los_usertask.h"

/* �������� ID ���� */
UINT32 Test1_Task_Handle;
UINT32 Test2_Task_Handle;

/*******************************************************************************
* @ ������   ��AppTaskCreat 
* @ ����˵�� �����񴴽���Ϊ�˷���������е����񴴽����������Է��������������
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 AppTaskCreat(void)
{
	/* ����һ���������ͱ�������ʼ��Ϊ LOS_OK */
	UINT32 uwRet = LOS_OK;
	
	uwRet = Creat_Test1_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test1_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Test2_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test2_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_Test1_Task 
* @ ����˵�� ������ Test1_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Test1_Task(void)
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Test1_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test1_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Test1_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_Test2_Task 
* @ ����˵�� ������ Test2_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Test2_Task(void)
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Test2_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test2_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Test2_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Test1_Task 
* @ ����˵�� ��Test1_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Test1_Task(void)
{
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LED2_TOGGLE;
		printf("���� 1 ������, ÿ 1000ticks ��ӡһ����Ϣ\r\n");
		LOS_TaskDelay(1000);
  }
}	

/*******************************************************************************
* @ ������   ��Test1_Task 
* @ ����˵�� ��Test1_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Test2_Task(void)
{
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LED1_TOGGLE;
		printf("���� 2 ������, ÿ 500ticks ��ӡһ����Ϣ\r\n");
		LOS_TaskDelay(500);
  }
}


