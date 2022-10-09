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
UINT32 Read_Task_Handle;
UINT32 Write_Task_Handle;

/* �����ֵ�źŵ�ID���� */
UINT32 BinarySem_Handle;
uint8_t ucValue[2] = {0x00, 0x00};

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
	
	/* ����һ����ֵ�ź��� */
  uwRet = LOS_BinarySemCreate(1,&BinarySem_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("BinarySem ����ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	}
	
	uwRet = Creat_Read_Task();
	if(uwRet != LOS_OK)
	{
		printf("Read_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Write_Task();
	if(uwRet != LOS_OK)
	{
		printf("Write_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_Read_Task 
* @ ����˵�� ������ Read_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Read_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Read_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Read_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Read_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_Write_Task 
* @ ����˵�� ������ Write_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Write_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Write_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Write_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Write_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Read_Task 
* @ ����˵�� ��Read_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Read_Task(void)
{
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LOS_SemPend(BinarySem_Handle, LOS_WAIT_FOREVER);
		//��ȡ��ֵ�ź��� BinarySem_Handle, û��ȡ����һֱ�ȴ�
		
		if(ucValue[0] == ucValue[1])
		{
			printf("\r\nSuccessful\r\n");
		}
		else
		{
			printf("\r\nFail\r\n");
		}
		LOS_SemPost(BinarySem_Handle);         //�ͷŶ�ֵ�ź��� BinarySem_Handle
	}
}	

/*******************************************************************************
* @ ������   ��Write_Task 
* @ ����˵�� ��Write_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Write_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		LOS_SemPend(BinarySem_Handle, LOS_WAIT_FOREVER);
		//��ȡ��ֵ�ź��� BinarySem_Handle, û��ȡ����һֱ�ȴ�
		ucValue[0]++;
		LOS_TaskDelay(1000);             /* ��ʱ1000Ticks */

		ucValue[1]++;
    LOS_SemPost(BinarySem_Handle);  //�ͷŶ�ֵ�ź��� BinarySem_Handle	
    LOS_TaskYield();                //����ʣ��ʱ��Ƭ������һ�������л�		
  }
}		


