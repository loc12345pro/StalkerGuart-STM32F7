#include "ultrasonic.h"
#include <stdio.h>
#include "init.h"

void ultrasonic_init()
{
	// Initialize trigger pin as output
	ultrasonic_init_trig();
	
	// Initialize echo pin as input
	ultrasonic_init_echo();
}

static void ultrasonic_init_trig()
{
	GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIO_LED clock */
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  gpio_init_structure.Pin = TRIGGER_PIN;
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_PULLDOWN;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
  HAL_GPIO_Init(TRIGGER_PORT, &gpio_init_structure);
    
  /* By default, turn off LED */
  HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);
}

static void ultrasonic_init_echo()
{
	GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIO_LED clock */
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  gpio_init_structure.Pin = ECHO_PIN;
  gpio_init_structure.Mode = GPIO_MODE_INPUT;
  gpio_init_structure.Pull = GPIO_PULLDOWN;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
  HAL_GPIO_Init(ECHO_PORT, &gpio_init_structure);
    
  /* By default, turn off LED */
  HAL_GPIO_WritePin(GPIOI, ECHO_PIN, GPIO_PIN_RESET);
}

static float ultrasonic_calc_distance()
{
	/* Preparations */
	uint32_t ms_time_passed = 0;
	
	/* Enable trigger pin in at least 10us */
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_SET);
	
	/* Start 10us counting timer */
	tim3_start();
	
	/* Set trigger pin to 0 until 10us has been counter */
	while (tim3_finished_counting == TRUE)
	{
		HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);
		
		/* Start 1ms timer*/
		tim4_start();
		
		/* Stop 10us timer */
		tim3_stop();
		
	}

	/* Start to count time in miliseconds */
	/* Count time until echo pin is set to 1 */
	while (HAL_GPIO_ReadPin(GPIOI, ECHO_PIN) != GPIO_PIN_SET)
	{
		if (tim4_finished_counting != TRUE)
		{
			ms_time_passed++;
			
			/* Reset timer4 counting flag */
			tim4_finished_counting = FALSE;
		}
	}
	
	/* Stop 1ms timer */
	tim4_stop();
	
	return ms_time_passed;
}

float ultrasonic_calc_distance_inch()
{
	 
}

float ultrasonic_calc_distance_cm()
{
	
}