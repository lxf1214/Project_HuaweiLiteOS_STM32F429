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
UINT32 LED_Task_Handle;
UINT32 Key_Task_Handle;

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
	
	uwRet = Creat_LED_Task();
	if(uwRet != LOS_OK)
	{
		printf("LED_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Key_Task();
	if(uwRet != LOS_OK)
	{
		printf("Key_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_LED_Task 
* @ ����˵�� ������ LED_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_LED_Task(void)
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "LED_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LED_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&LED_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_Key_Task 
* @ ����˵�� ������ Key_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Key_Task(void)
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Key_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��LED_Task 
* @ ����˵�� ��LED_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void LED_Task(void)
{
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LED2_TOGGLE;
		printf("LED �����������У�\n");
		LOS_TaskDelay(1000);
  }
}	

/*******************************************************************************
* @ ������   ��Key_Task 
* @ ����˵�� ��Key_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Key_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		/* K1 ������ */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			printf(" ���� LED ���� \n");
			uwRet = LOS_TaskSuspend(LED_Task_Handle);   /* ���� LED1 ���� */
			if(LOS_OK == uwRet)
			{
				printf(" ���� LED ����ɹ��� \n");
			}
		}
		
		/* K2 ������ */
		else if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			printf(" �ָ� LED ���� \n");
			uwRet = LOS_TaskResume(LED_Task_Handle);
			if(LOS_OK == uwRet)
			{
				printf(" �ָ� LED ����ɹ��� \n");
			}
		}
		LOS_TaskDelay(20);        /* 20ms ɨ��һ�� */
  }
}		


