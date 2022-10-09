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
UINT32 Receive_Task_Handle;
UINT32 Send_Task_Handle;

UINT32 Test_Queue_Handle;

/* ������Ϣ���г��� */
#define TEST_QUEUE_LEN  16
#define TEST_QUEUE_SIZE 16

/* ȫ�ֱ������� */
UINT32 send_data1 = 1;
UINT32 send_data2 = 2;

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
	
	/* ����һ�����Զ��� */
  uwRet = LOS_QueueCreate("Test_Queue",                        /* �������� */
	                       TEST_QUEUE_LEN,                       /* ���г��� */
	                       &Test_Queue_Handle,                   /* ����ID(���) */
	                       0,                                    /* ����ģʽ */                         
	                       TEST_QUEUE_SIZE);	                   /* �ڵ��С����λΪ1�ֽ� */
	
	if(uwRet != LOS_OK)
	{
		printf("Test_Task ���д���ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Receive_Task();
	if(uwRet != LOS_OK)
	{
		printf("Receive_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Send_Task();
	if(uwRet != LOS_OK)
	{
		printf("Send_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_Receive_Task 
* @ ����˵�� ������ Receive_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Receive_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Receive_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Receive_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Receive_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_Send_Task 
* @ ����˵�� ������ Send_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Send_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Send_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Send_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Send_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Receive_Task 
* @ ����˵�� ��Receive_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Receive_Task(void)
{
	UINT32 uwRet = LOS_OK;
	UINT32 *r_queue;
	UINT32 buffsize = 16;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		/* ���ж�ȡ���ȴ�ʱ��Ϊһֱ�ȴ� */
		uwRet = LOS_QueueRead(Test_Queue_Handle,             /* ��ȡ����ID(���) */
		                      &r_queue,                      /* ��ȡ��Ϣ����λ�� */
		                      buffsize,                      /* ��ȡ��Ϣ���� */ 
		                      LOS_WAIT_FOREVER);             /* �ȴ�ʱ��:һֱ�� */
    
		if(LOS_OK == uwRet)
		{
			printf(" ���ζ�ȡ������Ϣ��%d\n", *r_queue);
		}
		else
    {
			printf(" ��Ϣ��ȡ�����������0x%X\n", uwRet);
		}
	}
}	

/*******************************************************************************
* @ ������   ��Send_Task 
* @ ����˵�� ��Send_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Send_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		/* K1 ������ */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			/* ����Ϣд�뵽�����У��ȴ�ʱ��Ϊ 0 */
			uwRet = LOS_QueueWrite(Test_Queue_Handle,          /* д�����ID(���) */
			                       &send_data1,                /* д����Ϣ */
			                       sizeof(send_data1),         /* ��Ϣ���� */
														 0);   
			if(LOS_OK != uwRet)
			{
				printf(" ��Ϣ����д�뵽��Ϣ���У� ������� 0x%X\n",uwRet);
			}
		}
		
		/* K2 ������ */
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			/* ����Ϣд�뵽�����У��ȴ�ʱ��Ϊ 0 */
			uwRet = LOS_QueueWrite(Test_Queue_Handle,          /* д�����ID(���) */
			                       &send_data2,                /* д����Ϣ */
			                       sizeof(send_data2),         /* ��Ϣ���� */
														 0);   
			if(LOS_OK != uwRet)
			{
				printf(" ��Ϣ����д�뵽��Ϣ���У� ������� 0x%X\n",uwRet);
			}
		}
		LOS_TaskDelay(20);        /* 20ms ɨ��һ�� */
  }
}		


