#include "config.h"
#include <stdarg.h>
#include "stm32f1_adc.h"
#include "joystick.h"
#include "stm32f1_gpio.h"


static volatile uint16_t position1y;
static volatile uint16_t position2y;
static volatile uint16_t position1x;
static volatile uint16_t position2x;


void JOYSTICK_x_init(void){
	//BSP_GPIO_PinCfg(JOYSTICK_x_PORT, JOYSTICK_x_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	ADC_init();
}

void JOYSTICK_y_init(void){
	//BSP_GPIO_PinCfg(JOYSTICK_y_PORT, JOYSTICK_y_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	ADC_init();
}

uint16_t JOYSTICK_y_getValue(){
	position1x=ADC_getValue(ADC_2);
	return position1x;
}


uint16_t JOYSTICK_x_getValue(){
	position1y=ADC_getValue(ADC_3);
	return position1y;
}

void JOYSTICK2_x_init(void){
	//BSP_GPIO_PinCfg(JOYSTICK2_x_PORT, JOYSTICK2_x_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	ADC_init();
}

uint16_t JOYSTICK2_x_getValue(){
	position2x=ADC_getValue(ADC_11);
	return position2x;
}
