#include "stdafx.h"									
//code by </MATRIX>@Neod Anderjon
//author: Neod Anderjon
//====================================================================================================
//打印系统请求状态

uint32_t devID[3];									//芯片设备ID号存储数组

//获取CPU唯一ID
void Get_MCU_SerialNumID (void) 
{ 
	//取相关寄存器值
	devID[0] = *(vu32 *)(0x1FFFF7F0);  				//高字节
	devID[1] = *(vu32 *)(0x1FFFF7EC); 
	devID[2] = *(vu32 *)(0x1FFFF7E8);				//低字节
	
	if (SendDataCondition)
	{
		printf("\r\nChip SerialNum ID: %#08X-%08X-%08X\r\n", devID[0], devID[1], devID[2]);
		usart1WaitForDataTransfer();
	}
} 

//获取CPU主频
uint32_t Get_BSP_CPU_ClkFreq (void)            
{
    RCC_ClocksTypeDef rcc_clocks;
    RCC_GetClocksFreq(&rcc_clocks);               	//获取芯片的各种时钟频率
    return ((uint32_t)rcc_clocks.HCLK_Frequency); 	//返回HCLK时钟频率
}

//预调功能算法测试接口(PTFAI)
void PreTesFuncAlgInterface (void)
{
	__ShellHeadSymbol__; U1SD("PTFAT Tested Finished\r\n");
}

//显示系统当前信息
void displaySystemInfo (void)
{
	//打印系统状态信息
	if (SendDataCondition)
	{
		//开发信息
		__ShellHeadSymbol__; U1SD("Developer Information Display:\r\n");
		U1SD("\r\n"); U1SD(__Laboratory__); U1SD(" ["); U1SD(__Logo__); U1SD("] Support\r\n");
		U1SD("\r\nBased in STM32 Microchip Embedded Motion Controller(EMC)\r\n");
        usart1WaitForDataTransfer();		
		printf("\r\n"); printf(__Frame_Name__); printf(" Framework Support\r\n");
		usart1WaitForDataTransfer();		
        printf("\r\nCode by "); printf(__Organization__); printf("@"); printf(__Developer__); printf ("\r\n");
        usart1WaitForDataTransfer();		
		printf("\r\nVersion: "); printf(__Code_Version__); printf("\r\n");
        usart1WaitForDataTransfer();	
		
		//任务管理模式
		__ShellHeadSymbol__; U1SD("TaskManager Type: ");
		if (TMMS == Streak) 
			printf("</MATRIX> Streak TaskRun\r\n");	
		else if (TMMS == RTOS)					
		{
			printf(__OS_Version__); 
			usart1WaitForDataTransfer();
			printf(" Support\r\n");
		}
		usart1WaitForDataTransfer();
		
		//CPU信息
		__ShellHeadSymbol__; U1SD("CPU Resource Information:\r\n");	
		Get_MCU_SerialNumID();						//芯片ID
		printf("\r\nCPU Model: 		"); printf(__MCU_Model__); printf("\r\n");//芯片型号
        usart1WaitForDataTransfer();		
		printf("\r\nCPU HCLK:		%dHz\r\n", Get_BSP_CPU_ClkFreq());//时钟主频
        usart1WaitForDataTransfer();		
		printf("\r\nCPU Flash: 		"); printf(__MCU_Flash_Size__); printf("k\r\n");//flash
        usart1WaitForDataTransfer();		
		printf("\r\nCPU SRAM: 		"); printf(__MCU_SRAM_Size__); printf("k\r\n");//sram
        usart1WaitForDataTransfer();		
		
		//系统状态信息
		__ShellHeadSymbol__; U1SD("System Status Information:\r\n");	
		if (EW_Switch == EW_Enable)
		{
			printf("\r\nError Warning: 		%02d\r\n", Return_Error_Type);//错误警告
			usart1WaitForDataTransfer();		
		}
		if (Temp_Switch == Temp_Enable)
		{
			printf("\r\nMCU Temperature: 	%02.02f C\r\n", MCU_Temperature_Detector());//内部温度检测
			usart1WaitForDataTransfer();		
		}
		if (TMMS == RTOS)
		{
			printf("\r\nRTOS CPU Usage: 	%.2f%%\r\n", (float)RTOSCPUUsage / 100);//CPU占用率
			usart1WaitForDataTransfer();		
		}
		printf("\r\nMemory Usage: 		%d%%\r\n", mem_perused());//显示内存使用率
		usart1WaitForDataTransfer();		
	}
	
	if (pwsf == JBoot)
	{
		RTC_DataStorage(calendar);
		RTC_ReqOrderHandler();						//RTC时间
	}
	
	PreTesFuncAlgInterface();						//预调功能测试
	
	__ShellHeadSymbol__; U1SD("All Init Process Run Finished, You Can Start Your Work\r\n");
}

//====================================================================================================
//code by </MATRIX>@Neod Anderjon