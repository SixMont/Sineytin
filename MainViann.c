/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "button.h"
#include "stdbool.h"
#include <math.h>

#define square(a) (a)*(a)




void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BUTTON_U_GPIO, BUTTON_U_PIN);
}



static void process_ms(void){

	static volatile uint32_t t = 0;

	if(t){
		t--;
	}
}

void mvtCarre(uint16_t x){

	ILI9341_DrawFilledRectangle(20+x,20,10+x,10,ILI9341_COLOR_BLUE);
	HAL_Delay(10);
	ILI9341_DrawFilledRectangle(18+x,20,8+x,10,ILI9341_COLOR_WHITE);


}


/**Cette fonction fait appaeraitre un cercle aux coordonnées du carré qui moove sur le côté de l'écran
 * @params : x,y, coordonnées du centre du cercle
 * tir : Permet de savoir si on est au premier appel de la fonction, pour retenir la coordonnées x à laquelle a été initié le tir
 *
 *
 */


void Projectile(uint16_t x, uint16_t y, bool_e tir){


	static uint16_t xc;
	volatile r=6;

	if(tir==FALSE){

		 xc = x;

	}

	ILI9341_DrawFilledCircle(xc, y,r, ILI9341_COLOR_RED);
	//HAL_Delay(10);
	ILI9341_DrawFilledCircle(xc, y-2,r, ILI9341_COLOR_WHITE);

}

bool_e Collision(uint16_t yc,uint16_t xc,uint16_t r){

	if (sqrt(square((300-xc))+square((200-yc)))<=(r+10)){


		HAL_Delay(1000);

	}
	return TRUE;
}



int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premiï¿½re ï¿½tape de la fonction main().
    HAL_Init();

	//Initialisation de l'UART2 ï¿½ la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliï¿½es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigï¿½es vers la sonde de dï¿½bogage, la liaison UART ï¿½tant ensuite encapsulï¿½e sur l'USB vers le PC de dï¿½veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le pï¿½riphï¿½rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);



	//Ajouter dans la fonction main(), juste avant la boucle while(1) de tâche de fond :
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	BUTTON_init();
	//bool_e button;

	//button = !HAL_GPIO_ReadPin(BUTTON_U_GPIO, BUTTON_U_PIN);
	//ILI9341_DrawCircle(20,20,5,ILI9341_COLOR_BLUE);
	//ILI9341_DrawLine(20,20,100,20,ILI9341_COLOR_RED);
	//ILI9341_DrawLine(20,20,20,100,ILI9341_COLOR_RED);
	//ILI9341_Putc(110,11,'x',&Font_7x10,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	//ILI9341_Putc(15,110,'y',&Font_7x10,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	//ILI9341_Puts(200,200, "chaine", &Font_7x10, ILI9341_COLOR_BROWN,
	//ILI9341_COLOR_WHITE);


	//Ajouter dans la fonction main(), juste avant la boucle while(1) de tâche de fond :



	uint16_t x = 20;
	uint16_t y = 20;
	bool_e tir = FALSE;
	uint16_t timer = 100;
	ILI9341_DrawSquare(200,300,10,ILI9341_COLOR_GREEN);

	while(1)
	{
		x++;
		collision(yc,xc,r);
		move(x);

		if(readButton() || tir==TRUE){

			shot(x,y,tir);
			tir= TRUE;
			timer--;
			y++;
			}



			//ILI9341_Puts(110,100,'true',&Font_7x10,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);


	}

}







