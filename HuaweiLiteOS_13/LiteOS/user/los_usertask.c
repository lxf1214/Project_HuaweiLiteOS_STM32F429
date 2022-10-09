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
  * 实验平台:野火  STM32 F429 开发板  
  *
  ******************************************************************************
  */

#include "los_usertask.h"

UINT32 BoxMem[MEM_BOXSIZE * MEM_BLKSIZE];
UINT32 *p_Num = NULL;                       //指向读写内存池地址的指针
UINT32 *p_Initial = NULL;                   //保存初始化指针

/* 定义任务 ID 变量 */
UINT32 LED_Task_Handle;
UINT32 Key_Task_Handle;

/*******************************************************************************
* @ 函数名   ：AppTaskCreat 
* @ 功能说明 ：任务创建，为了方便管理，所有的任务创建函数都可以放在这个函数里面
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 AppTaskCreat(void)
{
	/* 定义一个返回类型变量，初始化为 LOS_OK */
	UINT32 uwRet = LOS_OK;
	
  uwRet = Creat_LED_Task();
	if(uwRet != LOS_OK)
	{
		printf("LED_Task 任务创建失败! 失败代码 0x%X\n", uwRet);
		return uwRet;
	}
	
  uwRet = Creat_Key_Task();
	if(uwRet != LOS_OK)
	{
		printf("Key_Task 任务创建失败! 失败代码 0x%X\n", uwRet);
		return uwRet;
	}	
	
	return LOS_OK;
}

/*******************************************************************************
* @ 函数名   ：Creat_LED_Task 
* @ 功能说明 ：创建 LED_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_LED_Task()
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 5;           //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "LED_Task";      //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)LED_Task;
	task_init_param.uwStackSize = 1024;       //栈大小
	
	uwRet = LOS_TaskCreate(&LED_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：Creat_Key_Task 
* @ 功能说明 ：创建 Key_Task 任务
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
UINT32 Creat_Key_Task()
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 4;           //任务优先级，数值越小，优先级越高
	task_init_param.pcName = "Key_Task";      //任务名
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Key_Task;
	task_init_param.uwStackSize = 1024;       //栈大小
	
	uwRet = LOS_TaskCreate(&Key_Task_Handle, &task_init_param);
	return uwRet;
}

/*******************************************************************************
* @ 函数名   ：LED_Task 
* @ 功能说明 ：LED_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void LED_Task(void)
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	/* 任务都是无限循环，不能返回 */
	while(1)
	{
		LED2_TOGGLE;
		LOS_TaskDelay(1000);                                     //延时1000个Tick
	}
}	


/*******************************************************************************
* @ 函数名   ：Key_Task 
* @ 功能说明 ：Key_Task 任务实现
* @ 参数     ：无
* @ 返回值   ：无
*******************************************************************************/
void Key_Task(void)
{
	//定义一个返回类型变量，初始化为 LOS_OK
	UINT32 uwRet = LOS_OK;
	
	printf("正在初始化静态内存池........................\n");
	/* 初始化内存池 */
	uwRet = LOS_MemboxInit( &BoxMem[0],                          //内存池地址
	                        MEM_BOXSIZE,                         //内存池大小
	                        MEM_BLKSIZE);                        //内存块大小
	if(uwRet != LOS_OK)
		printf("内存池初始化失败!\n");
	else
		printf("内存池初始化成功!\n");	
	
	/* 任务都是无限循环，不能返回 */
	while(1)
	{
		/* KEY1 被按下 */
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_PIN) == KEY_ON)
		{
			if(NULL == p_Num)
			{
				printf("正在向内存池分配内存.....................\n");
				/* 向已经初始化的内存池分配内存 */
				p_Num = (UINT32*)LOS_MemboxAlloc(BoxMem);
				if(NULL == p_Num)
					printf("分配内存失败!\n");
				else
				{
					printf("分配内存成功! 地址为 0x%X\n", (uint32_t)p_Num);
					/* 向 Test_Ptr 中写入数据：当前系统时间 */
					sprintf((char*)p_Num, "当前系统 TickCount = %d\n", (UINT32)LOS_TickCountGet());
					printf("写入的数据是 %s\n",(char*)p_Num);
				}
			}
			else
				printf("请先按下 KEY2 释放内存再分配!\n");
		}
		
		/* KEY2 被按下 */
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_PIN) == KEY_ON)
		{
			if(NULL != p_Num)
			{
				printf("清除前内存信息是 %s, 地址为 0x%X\n", (char*)p_Num, (uint32_t)p_Num);
				printf("正在清除 p_Num 的内容.....................\n");
        LOS_MemboxClr(BoxMem, p_Num);                               //清除 p_Num 地址的内容
				printf("清除后内存信息是 %s, 地址为 0x%X\n", (char*)p_Num, (uint32_t)p_Num);     
        printf("正在释放内存.....................\n");
        uwRet = LOS_MemboxFree(BoxMem, p_Num);
        if(LOS_OK == uwRet)
        {
					printf("内存释放成功!\n");          //内存释放成功
					p_Num = NULL;
				}					
				else
					printf("内存释放失败!\n");          //内存释放失败
			}		
			else 
				printf("请先按下 KEY1 分配内存再释放!\n");
		}
		LOS_TaskDelay(20);                        //每 20ms 扫描一次
	}
}		





