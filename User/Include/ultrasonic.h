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

#define TRIGGER_UP_TIME_US 15

#define CM_DIVIDER		58
#define INCH_DIVIDER	148

/* Exported functions ------------------------------------------------------- */
void ultrasonic_init(void);
static void ultrasonic_init_trig(void);
static void ultrasonic_init_echo(void);
static uint32_t ultrasonic_calc_distance(void);
float ultrasonic_calc_distance_inch(void);
float ultrasonic_calc_distance_cm(void);

#endif
