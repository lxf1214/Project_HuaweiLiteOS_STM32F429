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

#include "los_usertask.h"

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
	UINT32 uwRet = LOS_OK;                     //定义一个任务创建的返回值，默认为创建成功
	
	/* 板载相关初始化 */
	BSP_Init();
	
	printf("这是一个双向链表实验!\n");

	/* LiteOS 内核初始化 */
	uwRet = LOS_KernelInit();
	
	if(uwRet != LOS_OK)
	{
		printf("LiteOS 核心初始化失败！失败代码 0x%X\n",uwRet);
	  return LOS_NOK;
	}
	
	/* 任务创建 */
	AppTaskCreat();
	
	if(uwRet != LOS_OK)
	{
		printf("AppTaskCreate 创建任务失败！失败代码 0x%X\n",uwRet);
	  return LOS_NOK;		
	}
	
	/* 开启 LiteOS 任务调度 */
	LOS_Start();

	//正常情况下不会执行到这里
	while(1);
}
/*********************************************END OF FILE**********************/

