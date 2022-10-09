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

UINT32 TmrCb_Count1 = 0;
UINT32 TmrCb_Count2 = 0;

/* �������� ID ���� */
UINT16 Timer1_Handle;
UINT16 Timer2_Handle;

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
	
  /* ����һ�������ʱ�� */
	uwRet = LOS_SwtmrCreate(5000,                               //�����ʱ����ʱʱ��
	                        LOS_SWTMR_MODE_ONCE,                //�����ʱ��ģʽ һ��ģʽ
	                        (SWTMR_PROC_FUNC)Timer1_Callback,   //�����ʱ���Ļص�����
	                        &Timer1_Handle,                     //�����ʱ�� id
	                        0);
	if(uwRet != LOS_OK)
	{
		printf("�����ʱ��Timer1����ʧ�ܣ�\n");
		return uwRet;
	}
	
  /* ����һ�������ʱ�� */
	uwRet = LOS_SwtmrCreate(1000,                               //�����ʱ����ʱʱ��
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //�����ʱ��ģʽ һ��ģʽ
=======
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //�����ʱ��ģʽ һ��ģʽ
=======
<<<<<<< HEAD
	                        LOS_SWTMR_MODE_PERIOD,                //�����ʱ��ģʽ һ��ģʽ
=======
	                        LOS_SWTMR_MODE_PERIOD,              //�����ʱ��ģʽ ����ģʽ
>>>>>>> 3641d5e (提交文件)
>>>>>>> 917ff36 (提交文件)
>>>>>>> ead996f (更新文件)
	                        (SWTMR_PROC_FUNC)Timer2_Callback,   //�����ʱ���Ļص�����
	                        &Timer2_Handle,                     //�����ʱ�� id
	                        0);
	if(uwRet != LOS_OK)
	{
		printf("�����ʱ��Timer2����ʧ�ܣ�\n");
		return uwRet;
	}
	
	/* ����һ�������ʱ�� */ 
	uwRet = LOS_SwtmrStart(Timer1_Handle);
	if(LOS_OK != uwRet)
	{
		printf("start Timer1 failed\n");
		return uwRet;
	}
	else
	{
		printf("start Timer1 sucess\n");
	}
		
	/* ����һ�������ʱ�� */ 
	uwRet = LOS_SwtmrStart(Timer2_Handle);
	if(LOS_OK != uwRet)
	{
		printf("start Timer2 failed\n");
		return uwRet;
	}
	else
	{
		printf("start Timer2 sucess\n");
	}
	
	return LOS_OK;
}

/*******************************************************************************
* @ ������   ��Timer1_Callback 
* @ ����˵�� �������ʱ���ص�����1
* @ ����     ������1����������δʹ��
* @ ����ֵ   ����
*******************************************************************************/
void Timer1_Callback(UINT32 reg)
{
	UINT32 tick_num1;
	
	TmrCb_Count1++;                                     //ÿ�ص�һ�μ�һ
	LED1_TOGGLE;
	tick_num1 = (UINT32)LOS_TickCountGet();             //��ȡ�δ�ʱ���ļ���ֵ
	
	printf("Timer_CallBack_Count1 = %d\n", TmrCb_Count1);
	
	printf("tick_num1 = %d\n", tick_num1);
}	


/*******************************************************************************
* @ ������   ��Timer2_Callback 
* @ ����˵�� �������ʱ���ص�����2
* @ ����     ������1����������δʹ��
* @ ����ֵ   ����
*******************************************************************************/
void Timer2_Callback(UINT32 arg)
{
	UINT32 tick_num2;

  TmrCb_Count2++;                                     //ÿ�ص�һ�μ�һ
	LED2_TOGGLE;
	tick_num2 = (UINT32)LOS_TickCountGet();             //��ȡ�δ�ʱ���ļ���ֵ
	printf("Timer_CallBack2_Count2 = %d\n", TmrCb_Count2);
	
	printf("tick_num2 = %d\n", tick_num2);
}		

