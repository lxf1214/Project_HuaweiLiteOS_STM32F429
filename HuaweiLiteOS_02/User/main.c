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
#include "./led/bsp_led.h"

#include "los_sys.h"
#include "los_typedef.h"
#include "los_task.ph"


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
	/* ������س�ʼ�� */
	BSP_Init();
	LED1_ON;
	while(1);
}

/*********************************************END OF FILE**********************/

