#include "delay.h"
#include "init.h"

void delay(uint32_t micro_sec)
{
	/* Stop timer */
	timx_stop();
	
	/* Set flag to default value */
	timx_finished_counting = FALSE;
	
	/* Start timer */
	timx_start();
	
	/* Loop until the timer counts to micro_sec */
	while (micro_sec != 0)
	{
		if (timx_finished_counting == TRUE)
		{
			micro_sec--;
			timx_finished_counting = FALSE;
		}
	}
	
	/* Stop timer */
	timx_stop();
}

/* Reads a pulse (either HIGH or LOW) on a pin. For example, if value is HIGH, pulseIn() waits for 
 * the pin to go HIGH, starts timing, then waits for the pin to go LOW and stops timing. 
 * Returns the length of the pulse in microseconds or 0 if no complete pulse was received within the timeout. 
 */
uint32_t pulse_in(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState value)
{
	/* Preparations */
	uint32_t duration = 0;
	const uint32_t timeout = 1000000;
	uint32_t cur_time = 0;
	
	/* Start timer */
	timx_finished_counting = FALSE;
	timx_start();
	
	/* Listen for the value in "pin" of "port" is whether "value" state or not */
	while ((HAL_GPIO_ReadPin(port, pin) != value) && (cur_time < timeout))
	{
		if (timx_finished_counting == TRUE)
		{
			cur_time++;
			timx_finished_counting = FALSE;
		}
	}
	
	if (cur_time < timeout)
	{
		/* Initialize needed variables */
		cur_time = 0;
		timx_finished_counting = FALSE;
		
		/* Waits for the pin to go LOW if "value" is HIGH (or go HIGH 
		 * if "value is LOW") and stops timing 
		 */
		while ((HAL_GPIO_ReadPin(port, pin) == value) && (cur_time < timeout))
		{
			if (timx_finished_counting == TRUE)
			{
				cur_time++;
				duration++;
				timx_finished_counting = FALSE;
			}
		}
		
		/* If time out? */
		if (cur_time >= timeout)
		{
			duration = 0;
		}
	}
	
	/* Stop timer */
	timx_stop();
	timx_finished_counting = FALSE;
	
	return duration;
}
