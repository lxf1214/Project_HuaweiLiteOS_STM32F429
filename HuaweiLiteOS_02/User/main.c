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
  * 实验平台:野火  STM32 F429 开发板 
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
  * @brief  主函数
  * @param  无
  * @retval 无
	* @note   第一步：开发板硬件初始化
	*         第二步：创建 APP 应用任务
	*         第三步：启动LiteOS，开始多任务调度，启动失败则输出错误信息
  */
int main(void)
{
	/* 板载相关初始化 */
	BSP_Init();
	LED1_ON;
	while(1);
}

/*********************************************END OF FILE**********************/

