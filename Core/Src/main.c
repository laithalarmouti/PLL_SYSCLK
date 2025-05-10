#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0


void SystemClock_Config(uint8_t Clock_Freq);






//PRIVATE FUNCTION DEFINITIONS

void UART2_Init();
void Error_Handler();





UART_HandleTypeDef huart2;





int main(void)
{
	char msg[100];
	HAL_Init();

	SystemClock_Config(SYS_CLOCK_FREQ_50_MHZ);
//	SystemClock_Config(SYS_CLOCK_FREQ_80_MHZ)
//	SystemClock_Config(SYS_CLOCK_FREQ_100_MHZ)
	UART2_Init();

	memset(msg,0,sizeof(msg));
	sprintf(msg,"SYSCLK : %ld\r\n",HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"HCLK : %ld\r\n",HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK1 : %ld\r\n",HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	memset(msg,0,sizeof(msg));
	sprintf(msg,"PCLK2 : %ld\r\n",HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2,(uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	while(1);
	return 0;


}



void SystemClock_Config(uint8_t Clock_Freq)
{
	RCC_OscInitTypeDef osic_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;

	osic_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osic_init.HSIState = RCC_HSI_ON;
	osic_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osic_init.PLL.PLLState = RCC_PLL_ON;
	osic_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(Clock_Freq)
	{
		case SYS_CLOCK_FREQ_50_MHZ:
		{
			osic_init.PLL.PLLM = 16;
			osic_init.PLL.PLLN = 100;
			osic_init.PLL.PLLP = RCC_PLLP_DIV2;
			osic_init.PLL.PLLQ = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV1;
			FLatency = FLASH_ACR_LATENCY_1WS;

			break;
		}
		case SYS_CLOCK_FREQ_80_MHZ:
		{
			osic_init.PLL.PLLM = 16;
			osic_init.PLL.PLLN = 160;
			osic_init.PLL.PLLP = RCC_PLLP_DIV2;
			osic_init.PLL.PLLQ = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV1;
			FLatency = FLASH_ACR_LATENCY_2WS;
			break;
		}
		case SYS_CLOCK_FREQ_100_MHZ:
		{
			osic_init.PLL.PLLM = 16;
			osic_init.PLL.PLLN = 200;
			osic_init.PLL.PLLP = RCC_PLLP_DIV2;
			osic_init.PLL.PLLQ = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

			FLatency = FLASH_ACR_LATENCY_3WS;
			break;
		}
		default:
			return;
	}
	if(HAL_RCC_OscConfig(&osic_init) != HAL_OK)
	{
		Error_Handler();
	}
	if(HAL_RCC_ClockConfig(&clk_init,FLatency) != HAL_OK)
	{
		Error_Handler();
	}

	//SYSTICK CONFIG
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}




void Error_Handler()
{
	while(1);
}

void UART2_Init()
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		//ERROR
		Error_Handler();
	}

}


