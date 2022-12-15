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

void writeBUZZER(bool_e b)
{
	HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, b);
}

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;

void process_ms(void)
{
	if(t)
		t--;
}

//Fonctions Controle Joystick

//Fonction

int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);

//	writeBUZZER(1);

//	HAL_Delay(500);			//test buzzer mais ça marche pas

//	writeBUZZER(0);
	
	
	

	while(1)	//boucle de t�che de fond
	{

		if(!t)
		{
			t = 200;
			HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);
		}
	}
}

void state_machine(void)
{
	typedef enum
	{
		INIT = 0,
		JOUEUR1,
		JOUEUR2,
		PERD,
		GAGNE,
		MENU
	}state_e;
	static state_e state = INIT;
	switch(state)
	{
		case INIT:
						//initialiation du jeu
		state = MENU;
		break;
		case JOUEUR1:
						// 1 seul joueur 
		state = PERD;
		state = GAGNE;
		break;
		case JOUEUR2:
						// 2 joueurs
		state = PERD;
		state = GAGNE;
		break;
		case PERD:
						//perd
		state = MENU;
		break;
		case GAGNE:
						//gagne
		state = MENU;
		break;
		case MENU:
						//menu
		break;
		default:
	break;
	}
