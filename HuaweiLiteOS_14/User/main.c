/**
  ******************************************************************************
  * @file    main.c
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
#include "stm32f4xx.h"
#include "./Init/bsp_Init.h"

#include "los_usertask.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
	* @note   ��һ����������Ӳ����ʼ��
	*         �ڶ��������� APP Ӧ������
	*         ������������LiteOS����ʼ��������ȣ�����ʧ�������������Ϣ
  */
int main(void)
{
	UINT32 uwRet = LOS_OK;                     //����һ�����񴴽��ķ���ֵ��Ĭ��Ϊ�����ɹ�
	
	/* ������س�ʼ�� */
	BSP_Init();
	
	printf("����һ����̬�ڴ����ʵ��!\n");
		printf("ϵͳ��ʼ����ʱ���Ѿ������ڴ��ʼ�������Դ�ʱ�����ʼ��!\n");
	printf("����KEY1�����ڴ棬����KEY2�ͷ��ڴ�!\n\n");

	
	/* LiteOS �ں˳�ʼ�� */
	uwRet = LOS_KernelInit();
	
	if(uwRet != LOS_OK)
	{
		printf("LiteOS ���ĳ�ʼ��ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	  return LOS_NOK;
	}
	
	/* ���񴴽� */
	uwRet = AppTaskCreat();
	
	if(uwRet != LOS_OK)
	{
		printf("AppTaskCreate ��������ʧ�ܣ�ʧ�ܴ��� 0x%X\n",uwRet);
	  return LOS_NOK;		
	}
	
	/* ���� LiteOS ������� */
	LOS_Start();

	//��������²���ִ�е�����
	while(1);
}
/*********************************************END OF FILE**********************/

