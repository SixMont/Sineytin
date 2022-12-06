#include "config.h"
#include <stdarg.h>
#include "stm32f1_adc.h"
#include "joystick.h"
#include "stm32f1_gpio.h"


static volatile uint16_t positionX;



void JOYSTICK_x_init(void){
	//BSP_GPIO_PinCfg(JOYSTICK_x_PORT, JOYSTICK_x_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	ADC_init();
}

void JOYSTICK_y_init(void){
	//BSP_GPIO_PinCfg(JOYSTICK_y_PORT, JOYSTICK_y_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	ADC_init();
}

uint16_t JOYSTICK_x_getValue(){
	positionX=ADC_getValue(ADC_3);
	return positionX;
}
