#include "ultrasonic.h"
#include <stdio.h>
#include "init.h"

void ultrasonic_init(void)
{
	// Initialize trigger pin as output
	ultrasonic_init_trig();
	
	// Initialize echo pin as input
	ultrasonic_init_echo();
}

static void ultrasonic_init_trig(void)
{
	GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIOI clock */
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /* Configure the trigger pin */
  gpio_init_structure.Pin = TRIGGER_PIN;
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_PULLDOWN;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
  HAL_GPIO_Init(TRIGGER_PORT, &gpio_init_structure);
    
  /* By default, set pin to 0 */
  HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);
}

static void ultrasonic_init_echo(void)
{
	GPIO_InitTypeDef  gpio_init_structure;

  /* Enable the GPIOI clock */
  __HAL_RCC_GPIOI_CLK_ENABLE();

  /* Configure the GPIO echo pin */
  gpio_init_structure.Pin = ECHO_PIN;
  gpio_init_structure.Mode = GPIO_MODE_INPUT;
  gpio_init_structure.Pull = GPIO_PULLDOWN;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  
  HAL_GPIO_Init(ECHO_PORT, &gpio_init_structure);
}

static uint32_t ultrasonic_calc_distance(void)
{
	/* Preparations */
	uint32_t ms_time_passed = 0;
	uint8_t trig_up_time = 0;
	
	/* Enable trigger pin in at least 10us */
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_SET);
	
	/* Start 10us counting timer */
	timx_finished_counting = FALSE;
	timx_start();
	
	/* Set trigger pin to 0 until 15us has been counted */
	while (trig_up_time != TRIGGER_UP_TIME_US)
	{
		if (timx_finished_counting == TRUE)
		{
			trig_up_time++;
			
			/* Reset timer counting flag */
			timx_finished_counting = FALSE;
		}
	}
	
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);

	/* Start to count time in miliseconds */
	/* Count time until echo pin is set to 1 */
	while (HAL_GPIO_ReadPin(GPIOI, ECHO_PIN) != GPIO_PIN_SET)
	{
		if (timx_finished_counting != TRUE)
		{
			ms_time_passed++;
			
			/* Reset timer counting flag */
			timx_finished_counting = FALSE;
		}
	}
	
	/* Stop 1ms timer */
	timx_stop();
	
	return ms_time_passed;
}

float ultrasonic_calc_distance_inch(void)
{
	return 1.0f * ultrasonic_calc_distance() / INCH_DIVIDER;
}

float ultrasonic_calc_distance_cm(void)
{
	return 1.0f * ultrasonic_calc_distance() / CM_DIVIDER;
}
