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


/* ����ʱ���־��Ŀ��ƿ� */
static EVENT_CB_S EventGroup_CB;

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
	
	/* ����һ���¼���־ */
  uwRet = LOS_EventInit(&EventGroup_CB);
	
	if(uwRet != LOS_OK)
	{
		printf("EventGroup_CB �¼���־�鴴��ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	}
	
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
UINT32 Creat_LED_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 3;                //�������ȼ�����ֵԽС�����ȼ�Խ��
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
UINT32 Creat_Key_Task()
{
	//����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ
	UINT32 uwRet = LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;                //�������ȼ�����ֵԽС�����ȼ�Խ��
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
	UINT32 uwRet;
	/* ������һ������ѭ�������ܷ��� */
	while(1)
	{
		//�ȴ��¼���־λ
    uwRet = LOS_EventRead(&EventGroup_CB,             //�¼���־�����
		                      KEY1_EVENT | KEY2_EVENT,    //�ȴ��������Ȥ���¼�
                          LOS_WAITMODE_AND,           //�ȴ���λ������λ
		                      LOS_WAIT_FOREVER);          //�����ڵȴ�
		if((uwRet & (KEY1_EVENT | KEY2_EVENT)) == (KEY1_EVENT | KEY2_EVENT))
		{
			/* ���������ɲ���ȷ */
			printf("KEY1 �� KEY2 ������\n");
			LED1_TOGGLE;
			LOS_EventClear(&EventGroup_CB, ~KEY1_EVENT);  //����¼���־λ
			LOS_EventClear(&EventGroup_CB, ~KEY2_EVENT);  //����¼���־λ
		}
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
		/* KEY1 ������ */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			printf("KEY1 ������\n");
			/* ����һ���¼� */
			LOS_EventWrite(&EventGroup_CB, KEY1_EVENT);
		}
		
		/* KEY2 ������ */
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			printf("KEY2 ������\n");
			/* ����һ���¼� */
			LOS_EventWrite(&EventGroup_CB, KEY2_EVENT);
		}
		
	}
}		

