#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TRIGGER_PIN		GPIO_PIN_2
#define TRIGGER_PORT	GPIOI
#define ECHO_PIN			GPIO_PIN_3
#define ECHO_PORT			GPIOI

#define CM_DIVIDER		

/* Exported functions ------------------------------------------------------- */
void ultrasonic_init();
static void ultrasonic_init_trig();
static void ultrasonic_init_echo();
static float ultrasonic_calc_distance();
float ultrasonic_calc_distance_inch();
float ultrasonic_calc_distance_cm();

#endif