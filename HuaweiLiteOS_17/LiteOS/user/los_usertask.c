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

extern LITE_OS_SEC_BSS UINT8* m_aucSysMem0;

UINT32 Test_Task_Handle;
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
	
  uwRet = Creat_Test_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test_Task ���񴴽�ʧ��!\n");
	}	
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
	
	printf("˫�������ʼ����............\n");
	LOS_DL_LIST *head;                         //����һ��˫�������ͷ�ڵ�
	head = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST)); //��̬����ͷ�ڵ��ڴ�
	LOS_ListInit(head);                        //��ʼ��˫������
	if(!LOS_ListEmpty(head))                   //�ж��Ƿ��ʼ���ɹ�
	{
		printf("˫�������ʼ��ʧ��!\n");
	}
	else
	{
		printf("˫�������ʼ���ɹ�!\n");
	}
	
	printf("��ӽڵ��β�ڵ�............\n");  //����ڵ㣺˳��������ĩβ����
	
	//��̬�����һ���ڵ������
	LOS_DL_LIST *node1 = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	//��̬����ڶ����ڵ������
	LOS_DL_LIST *node2 = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	//��̬����β�ڵ������
	LOS_DL_LIST *tail = (LOS_DL_LIST*)LOS_MemAlloc(m_aucSysMem0, sizeof(LOS_DL_LIST));
	
	printf("��ӵ�һ���ڵ���ڶ����ڵ�............\n");
	LOS_ListAdd(head, node1);                   //��ӵ�һ���ڵ㣬������ͷ�ڵ���
	LOS_ListAdd(node1, node2);                  //��ӵڶ����ڵ㣬�����ڵ�һ���ڵ���
	if((node1->pstPrev == head) && (node2->pstPrev == node1))  //�ж��Ƿ����ɹ�
	{
		printf("��ӽڵ�ɹ�!\n");
	}
	else
	{
		printf("��ӽڵ�ʧ��!\n");
	}
	
	printf("��β�ڵ����˫�������ĩβ............\n");	
	LOS_ListTailInsert(head, tail);              //��β�ڵ����˫�������ĩβ
	if(tail->pstPrev == node2)                   //�ж��Ƿ����ɹ�
	{
		printf("����β�ڵ���ӳɹ�!\n");
	}
	else
	{
		printf("����β�ڵ����ʧ��!\n");
	}	
	
	printf("ɾ���ڵ�............\n");	           //ɾ�����нڵ�
  LOS_ListDelete(node1);	                     //ɾ����һ���ڵ�
	LOS_MemFree(m_aucSysMem0, node1);            //�ͷŵ�һ���ڵ���ڴ�
	if(head->pstNext == node2)                   //�ж��Ƿ�ɾ���ɹ�
	{
		printf("ɾ���ڵ�ɹ�!\n");
	}
	else
	{
		printf("ɾ���ڵ�ʧ��!\n");
	}	
	
	while(1)
	{
		LED2_TOGGLE;
		printf("����������!\n");
		LOS_TaskDelay(2000);
	}
}	

