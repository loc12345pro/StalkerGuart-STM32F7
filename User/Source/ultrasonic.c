#include "ultrasonic.h"
#include <stdio.h>
#include "init.h"
#include "delay.h"

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
	uint32_t us_time_passed = 0;
	
	/* Make sure disable trigger pin */
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);
	delay(2);
	
	/* Enable trigger pin in 15us (at least 10us) */
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_SET);
	delay(15);
	
	/* Disable the trigger pin */
	HAL_GPIO_WritePin(GPIOI, TRIGGER_PIN, GPIO_PIN_RESET);

	/* Calculate pulse-width between SET state and RESET state of echo pin */
	us_time_passed = pulse_in(GPIOI, ECHO_PIN, GPIO_PIN_SET);

	return us_time_passed;
}

float ultrasonic_calc_distance_inch(void)
{
	return 1.0f * ultrasonic_calc_distance() / INCH_DIVIDER;
}

float ultrasonic_calc_distance_cm(void)
{
	return 1.0f * ultrasonic_calc_distance() / CM_DIVIDER;
}
