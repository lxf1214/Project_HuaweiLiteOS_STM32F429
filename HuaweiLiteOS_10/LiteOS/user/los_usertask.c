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
UINT32 HighPriority_Task_Handle;
UINT32 MidPriority_Task_Handle;
UINT32 LowPriority_Task_Handle;

/* �����ֵ�źŵ�ID���� */
UINT32 Mutex_Handle;


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
	
	/* ����һ�������� */
  uwRet = LOS_MuxCreate(&Mutex_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("Mutex ����ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	}
	
	uwRet = Creat_HighPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("HighPriority_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_MidPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("MidPriority_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_LowPriority_Task();
	if(uwRet != LOS_OK)
	{
		printf("LowPriority_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_HighPriority_Task 
* @ ����˵�� ������ HighPriority_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_HighPriority_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 3;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "HighPriority_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)HighPriority_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&HighPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_MidPriority_Task 
* @ ����˵�� ������ MidPriority_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_MidPriority_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "MidPriority_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)MidPriority_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&MidPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_LowPriority_Task 
* @ ����˵�� ������ LowPriority_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_LowPriority_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "LowPriority_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LowPriority_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&LowPriority_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��HighPriority_Task 
* @ ����˵�� ��HighPriority_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void HighPriority_Task(void)
{
	UINT32 uwRet = LOS_OK;
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		//��ȡ��ֵ�ź��� BinarySem_Handle��û��ȡ����һֱ�ȴ�
		uwRet = LOS_MuxPend(Mutex_Handle, LOS_WAIT_FOREVER);
		
		if(uwRet == LOS_OK)
		{
			printf("HighPriority_Task Running!\n");
		}
		
		LED1_TOGGLE;
		LOS_MuxPost(Mutex_Handle);                 //�ͷŶ�ֵ�ź��� BinarySem_Handle
		
		LOS_TaskDelay(1000);                           //��ʱ1000Ticks
		
	}
}	

/*******************************************************************************
* @ ������   ��MidPriority_Task 
* @ ����˵�� ��MidPriority_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void MidPriority_Task(void)
{
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
    printf("MidPriority_Task Running��\n");
		LOS_TaskDelay(100);               //ÿ100msɨ��һ��
  }
}		

/*******************************************************************************
* @ ������   ��LowPriority_Task 
* @ ����˵�� ��LowPriority_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void LowPriority_Task(void)
{
	UINT32 uwRet = LOS_OK;
	static uint32_t i;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		//��ȡ��ֵ�ź��� BinarySem_Handle��û��ȡ����һֱ�ȴ�
		uwRet = LOS_MuxPend(Mutex_Handle, LOS_WAIT_FOREVER);
		if(uwRet == LOS_OK)
		{
			printf("LowPriority_Task Running!\n");
		}
		
		LED2_TOGGLE;
		
		for(i=0; i<2000000; i++)
		{
			//ģ������ȼ�����ռ���ź���
			//����ʣ��ʱ��Ƭ������һ�������л�
			LOS_TaskYield();
		}
		
		printf("LowPriority_Task �ͷŻ�������\r\n");
		LOS_MuxPost(Mutex_Handle);                 //�ͷŶ�ֵ�ź��� BinarySem_Handle
		
		LOS_TaskDelay(1000);                           //��ʱ1000Ticks
  }
}		

