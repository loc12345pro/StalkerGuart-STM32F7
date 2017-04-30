#ifndef _INIT_H_
#define _INIT_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TIM_HandleTypeDef tim3Handle;
extern uint8_t tim3_finished_counting;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TRUE 1
#define FALSE 0

/* Exported functions ------------------------------------------------------- */
void SystemClock_Config(void);
void Error_Handler(void);
void MPU_Config(void);
void CPU_CACHE_Enable(void);

void system_init(void);
void lcd_init(void);

void tim3_init(void);
void tim3_start(void);
void tim3_stop(void);

#endif
