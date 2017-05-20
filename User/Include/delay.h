#ifndef _DELAY_H_
#define _DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void delay(uint32_t micro_sec);
uint32_t pulse_in(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState value);

#endif
