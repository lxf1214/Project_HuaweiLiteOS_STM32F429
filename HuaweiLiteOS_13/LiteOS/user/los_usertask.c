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

UINT32 BoxMem[MEM_BOXSIZE * MEM_BLKSIZE];
UINT32 *p_Num = NULL;                       //ָ���д�ڴ�ص�ַ��ָ��
UINT32 *p_Initial = NULL;                   //�����ʼ��ָ��

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
		printf("LED_Task ���񴴽�ʧ��! ʧ�ܴ��� 0x%X\n", uwRet);
		return uwRet;
	}
	
  uwRet = Creat_Key_Task();
	if(uwRet != LOS_OK)
	{
		printf("Key_Task ���񴴽�ʧ��! ʧ�ܴ��� 0x%X\n", uwRet);
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
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;           //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "LED_Task";      //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LED_Task;
	task_init_param.uwStackSize = 1024;       //ջ��С
	
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
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;           //�������ȼ�����ֵԽС�����ȼ�Խ��
	task_init_param.pcName = "Key_Task";      //������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;
	task_init_param.uwStackSize = 1024;       //ջ��С
	
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
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	/* ����������ѭ�������ܷ��� */
	while(1)
	{
		LED2_TOGGLE;
		LOS_TaskDelay(1000);                                     //��ʱ1000��Tick
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
	//����һ���������ͱ�������ʼ��Ϊ LOS_OK
	UINT32 uwRet = LOS_OK;
	
	printf("���ڳ�ʼ����̬�ڴ��........................\n");
	/* ��ʼ���ڴ�� */
	uwRet = LOS_MemboxInit( &BoxMem[0],                          //�ڴ�ص�ַ
	                        MEM_BOXSIZE,                         //�ڴ�ش�С
	                        MEM_BLKSIZE);                        //�ڴ���С
	if(uwRet != LOS_OK)
		printf("�ڴ�س�ʼ��ʧ��!\n");
	else
		printf("�ڴ�س�ʼ���ɹ�!\n");	
	
	/* ����������ѭ�������ܷ��� */
	while(1)
	{
		/* KEY1 ������ */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			if(NULL == p_Num)
			{
				printf("�������ڴ�ط����ڴ�.....................\n");
				/* ���Ѿ���ʼ�����ڴ�ط����ڴ� */
				p_Num = (UINT32*)LOS_MemboxAlloc(BoxMem);
				if(NULL == p_Num)
					printf("�����ڴ�ʧ��!\n");
				else
				{
					printf("�����ڴ�ɹ�! ��ַΪ 0x%X\n", (uint32_t)p_Num);
					/* �� Test_Ptr ��д�����ݣ���ǰϵͳʱ�� */
					sprintf((char*)p_Num, "��ǰϵͳ TickCount = %d\n", (UINT32)LOS_TickCountGet());
					printf("д��������� %s\n",(char*)p_Num);
				}
			}
			else
				printf("���Ȱ��� KEY2 �ͷ��ڴ��ٷ���!\n");
		}
		
		/* KEY2 ������ */
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			if(NULL != p_Num)
			{
				printf("���ǰ�ڴ���Ϣ�� %s, ��ַΪ 0x%X\n", (char*)p_Num, (uint32_t)p_Num);
				printf("������� p_Num ������.....................\n");
        LOS_MemboxClr(BoxMem, p_Num);                               //��� p_Num ��ַ������
				printf("������ڴ���Ϣ�� %s, ��ַΪ 0x%X\n", (char*)p_Num, (uint32_t)p_Num);     
        printf("�����ͷ��ڴ�.....................\n");
        uwRet = LOS_MemboxFree(BoxMem, p_Num);
        if(LOS_OK == uwRet)
        {
					printf("�ڴ��ͷųɹ�!\n");          //�ڴ��ͷųɹ�
					p_Num = NULL;
				}					
				else
					printf("�ڴ��ͷ�ʧ��!\n");          //�ڴ��ͷ�ʧ��
			}		
			else 
				printf("���Ȱ��� KEY1 �����ڴ����ͷ�!\n");
		}
		LOS_TaskDelay(20);                        //ÿ 20ms ɨ��һ��
	}
}		





