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

UINT32 Test_Task_Handle;
//�����ֵ�ź���
UINT32 BinarySem1_Handle;
UINT32 BinarySem2_Handle;

/*******************************************************************************
* @ ������   ��AppTaskCreat 
* @ ����˵�� �����񴴽���Ϊ�˷���������е����񴴽����������Է��������������
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void AppTaskCreat(void)
{
	UINTPTR uvIntSave;
	/* ����һ���������ͱ�������ʼ��Ϊ LOS_OK */
	UINT32 uwRet = LOS_OK;
	
  uwRet = LOS_BinarySemCreate(0, &BinarySem1_Handle);
	if(uwRet != LOS_OK)
	{
		printf("BinarySem1_Handle ��ֵ�ź�������ʧ��!\n");
	}
	
	uwRet = LOS_BinarySemCreate(0, &BinarySem2_Handle);
	if(uwRet != LOS_OK)
	{
		printf("BinarySem2_Handle ��ֵ�ź�������ʧ��!\n");
	}
	
  uwRet = Creat_Test_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test_Task ���񴴽�ʧ��!\n");
	}	
	
	uvIntSave = LOS_IntLock();                       //���������ж�
	
	//����Ӳ���жϣ���������Ӳ���жϲ�ע��Ӳ���жϴ�����
	LOS_HwiCreate(KEY1_INT_EXTI_IRQ,
	//ƽ̨���ж������ţ������� stm32fxxx.h �ҵõ����������� bsp_exti.h ���¶�����
	              0,                    //Ӳ���ж����ȼ�
	              0,                    //Ӳ���ж�ģʽ
	              KEY1_IRQHandler,      //�жϷ�����
                0);                   //����Ӳ���ж�ʱʹ�õ��жϴ��������������

	//����Ӳ���жϣ���������Ӳ���жϲ�ע��Ӳ���жϴ�����
	LOS_HwiCreate(KEY2_INT_EXTI_IRQ,
	//ƽ̨���ж������ţ������� stm32fxxx.h �ҵõ����������� bsp_exti.h ���¶�����
	              0,                    //Ӳ���ж����ȼ�
	              0,                    //Ӳ���ж�ģʽ
	              KEY2_IRQHandler,      //�жϷ�����
                0);                   //����Ӳ���ж�ʱʹ�õ��жϴ��������������
  
	LOS_IntRestore(uvIntSave);          //�ָ������ж�
}

/*******************************************************************************
* @ ������   ��Creat_Test_Task 
* @ ����˵�� ������ Test_Task ����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
UINT32 Creat_Test_Task()
{
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;           //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Test_Task";      //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test_Task;
	task_init_param.uwStackSize = 1024;       //ջ��С
	
	uwRet = LOS_TaskCreate(&Test_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ ������   ��Test_Task 
* @ ����˵�� ���ڴ��ڴ�ӡ�����жϵ���Ϣ
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void Test_Task(void)
{
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	/* ����������ѭ�������ܷ��� */
	while(1)
	{
		uwRet = LOS_SemPend(BinarySem1_Handle,0);
		if(uwRet == LOS_OK)
		{
			printf("�����жϵ��� KEY1!\n");
		}//��ȡ��ֵ�ź�����û��ȡ�򲻵ȴ�
		
		uwRet = LOS_SemPend(BinarySem2_Handle,0);
		if(uwRet == LOS_OK)
		{
			printf("�����жϵ��� KEY2!\n");
		}//��ȡ��ֵ�ź�����û��ȡ�򲻵ȴ�
		LOS_TaskDelay(20);
	}
}	

/*******************************************************************************
* @ ������   ��KEY1_IRQHandler 
* @ ����˵�� ���жϷ�����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void KEY1_IRQHandler(void)
{
	//ȷ���Ƿ������ EXTI Line �ж�
	if(EXTI_GetFlagStatus(KEY1_INT_EXTI_LINE) != RESET)
	{
		LOS_SemPost(BinarySem1_Handle);    //�ͷŶ�ֵ�ź��� BinarySem1_Handle
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
	}
}		


/*******************************************************************************
* @ ������   ��KEY2_IRQHandler 
* @ ����˵�� ���жϷ�����
* @ ����     ����
* @ ����ֵ   ����
*******************************************************************************/
void KEY2_IRQHandler(void)
{
	//ȷ���Ƿ������ EXTI Line �ж�
	if(EXTI_GetFlagStatus(KEY2_INT_EXTI_LINE) != RESET)
	{
		LOS_SemPost(BinarySem2_Handle);    //�ͷŶ�ֵ�ź��� BinarySem2_Handle
		//����жϱ�־λ
		EXTI_ClearITPendingBit(KEY2_INT_EXTI_LINE);
	}
}		





