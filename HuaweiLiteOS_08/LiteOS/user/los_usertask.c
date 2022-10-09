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
UINT32 Pend_Task_Handle;
UINT32 Post_Task_Handle;

/* �����ֵ�źŵ�ID���� */
UINT32 CountSem_Handle;


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
  uwRet = LOS_SemCreate(5,&CountSem_Handle);
	
	if(uwRet != LOS_OK)
	{
		printf("CountSem ����ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	}
	
	uwRet = Creat_Pend_Task();
	if(uwRet != LOS_OK)
	{
		printf("Pend_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	uwRet = Creat_Post_Task();
	if(uwRet != LOS_OK)
	{
		printf("Post_Task ���񴴽�ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
		return uwRet;
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Creat_Pend_Task 
* @ ����˵�� ������ Pend_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Pend_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Pend_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Pend_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Pend_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Creat_Post_Task 
* @ ����˵�� ������ Post_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Post_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;                //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Post_Task";         //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Post_Task;
	task_init_param.uwStackSize = 1024;            //ջ��С
	
	uwRet = LOS_TaskCreate(&Post_Task_Handle, &task_init_param);
	
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Pend_Task 
* @ ����˵�� ��Pend_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Pend_Task(void)
{
	UINT32 uwRet = LOS_OK;
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		if( Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			/* ��ȡһ�������ź������ȴ�ʱ��Ϊ0 */
			uwRet = LOS_SemPend(CountSem_Handle,0);
			
			if(LOS_OK == uwRet)
			{
				printf("\r\nKEY1�����£��ɹ����뵽ͣ��λ��\r\n");
			}
			else
			{
				printf("\r\nKEY1�����£�������˼������ͣ����������\r\n");
			}				
		}
		LOS_TaskDelay(20);               //ÿ20msɨ��һ��
	}
}	

/*******************************************************************************
* @ ������   ��Post_Task 
* @ ����˵�� ��Post_Task ����ʵ��
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Post_Task(void)
{
	UINT32 uwRet = LOS_OK;
	
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		if( Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			/* �ͷ�һ�������ź�����LiteOS�ļ����ź�������һֱ�ͷţ��ڱ����ע��һ�¼��� */
			uwRet = LOS_SemPost(CountSem_Handle);
			
			if(LOS_OK == uwRet)
			{
				printf("\r\nKEY2�����£��ͷ�һ��ͣ��λ��\r\n");
			}
			else
			{
				printf("\r\nKEY2�����£������޳�λ�����ͷţ�\r\n");
			}				
		}
		LOS_TaskDelay(20);               //ÿ20msɨ��һ��
  }
}		


