/* (à mettre dans le header)
#if BLUEPILL
	#define LED_GREEN_GPIO		GPIOC
	#define LED_GREEN_PIN		GPIO_PIN_13
//___________________________________________________________________
	#define BUZZER_GPIO			GPIOA
	#define BUZZER_PIN			GPIO_PIN_8
//___________________________________________________________________
	#define BLUE_BUTTON_GPIO	GPIOA
	#define BLUE_BUTTON_PIN 	GPIO_PIN_15		//Pas de bouton sur la bluepill, choisissez le port souhait� si vous en reliez un.
#endif
*/
  
void writeBUZZER(bool_e b)
{
	HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, b);
}

int main(void)
{
  writeBUZZER(1);

	HAL_Delay(500);			//test buzzer mais ça marche pas

	writeBUZZER(0);
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
						// 1 seul joueur démmarrer
		state = PERD;
		state = GAGNE;
		break;
		case JOUEUR2:
						// 2 joueur
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
}
