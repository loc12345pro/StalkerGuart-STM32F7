#ifndef _INIT_H_
#define _INIT_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TIM_HandleTypeDef timxHandle;
extern volatile uint8_t timx_finished_counting;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0

/* User can use this section to tailor TIMx instance used and associated resources */
/* Definition for TIMx clock resources */
#define TIMx                           TIM3
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM3_IRQn
#define TIMx_IRQHandler                TIM3_IRQHandler

/* Exported functions ------------------------------------------------------- */
void SystemClock_Config(void);
void Error_Handler(void);
void MPU_Config(void);
void CPU_CACHE_Enable(void);

void system_init(void);
void lcd_init(void);

void timx_init(void);
void timx_start(void);
void timx_stop(void);

#endif
