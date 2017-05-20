/**
 ******************************************************************************
 * @file    Templates/Src/main.c 
 * @author  MCD Application Team
 * @version V1.0.3
 * @date    22-April-2016 
 * @brief   STM32F7xx HAL API Template project 
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "init.h"
#include "stm32746g_discovery_lcd.h"
#include "ultrasonic.h"
#include "delay.h"

/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup Templates
 * @{
 */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MAX_STR 100

/* TIM handle declaration */
TIM_HandleTypeDef timxHandle;
volatile uint8_t timx_finished_counting = FALSE;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* Preparations */
	uint8_t str[MAX_STR];
	float range_cm = 0.0f;
	
	/* System initialization */
	system_init();
	
  /* Add code here */
  BSP_LED_Init(LED1);
  BSP_LED_On(LED1);
 
  /* LCD Initialization */ 
	lcd_init();
	
	/* Timer 3 */
	timx_init();
	
	/* Ultrasonic initialization */
	ultrasonic_init();
	
	/* Infinite loop */
	while (1)
	{
		/* Calculate distance in cemtimeters */
		range_cm = ultrasonic_calc_distance_cm();
		if (range_cm == 0)
		{
			BSP_LCD_DisplayStringAtLine(0, (uint8_t*)"Can't detect range...");
		}
		else 
		{
			sprintf((char*)str, "Distance: %.2f (cm)", range_cm);
			BSP_LCD_DisplayStringAtLine(0, str);
		}
		
		/* Display the result for a mount of time */
		delay(200000);
		
		/* Clear LCD */
		BSP_LCD_ClearStringLine(0);
	}
}

/**
 * @}
 */ 

/**
 * @}
 */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
