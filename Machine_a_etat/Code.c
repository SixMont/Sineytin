#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "stm32f1_adc.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "joystick.h"

static int xJoueur=120;
static int yJoueur=20;

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}

void writeBUZZER(bool_e b)
{
	HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, b);
}

bool_e readButton1(void)
{
	return !HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN);
}

//Fonctions Controle carré

void JOYSTICK_move_x(void){
	while(1){
		if (JOYSTICK_x_getValue()>2200){
			JOYSTICK_move_x_GAUCHE();
		}
		if (JOYSTICK_x_getValue()<1520){
			JOYSTICK__move_x_DROITE();
		}
	}
}

void JOYSTICK__move_x_DROITE(void){
	if (xJoueur>20){
		ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur-5,yJoueur,5,ILI9341_COLOR_BLUE);
		xJoueur-=5;
	}
}

void JOYSTICK_move_x_GAUCHE(void){
	if (xJoueur<220){
		ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur+5,yJoueur,5,ILI9341_COLOR_BLUE);
		xJoueur+=5;
	}
}

//ecran defaite

void Ecran_defaite(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "GAME OVER", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_RED);
	ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int sortir=0;

		while(sortir==0){

			ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton1()){
				sortir=1;

			}
		}
}
//ecran victoire

void Ecran_victoire(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "SUCCESS", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_GREEN);
	ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int sortir=0;

		while(sortir==0){

			ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton1()){
				sortir=1;

			}
		}
}
//ecran titre

int Ecran_titre_jeu(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "SINEYTIN", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(95,280, "leave", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int entrer=0;
	int sortir=0;

		while(sortir==0){

			if (JOYSTICK_y_getValue()>2200){
				entrer=1;
			}

			if(entrer==-1){ //mode leave
				ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
				ILI9341_Puts(95,280, "leave", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

				if(readButton1()){
					sortir=-1;
				}
			}

			if (JOYSTICK_y_getValue()<1520){
				entrer=-1;
			}
			if (entrer==1){ //mode start
				ILI9341_Puts(95,280, "leave", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
				ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

				if(readButton1()){
					sortir=1;
				}
			}
		}
		return sortir;
}

//Fonctions Menu

int Ecran_Selection(void){
	FOND_Espace();
	ILI9341_Puts(65,100, "Solo", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(45,200, "2 players", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int i=0;
	int sortir=0;

	while(sortir==0){

		if (JOYSTICK_y_getValue()>2200){
			i=1;
		}
		if(i==-1){//mode 2 joueurs
			ILI9341_Puts(65,100, "Solo", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
			ILI9341_Puts(45,200, "2 players", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);
			if(readButton1()){
											sortir=-1;
			}
		}
		if (JOYSTICK_y_getValue()<1520){
			i=-1;
		}
		if (i==1){//mode solo
			ILI9341_Puts(45,200, "2 players", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
			ILI9341_Puts(65,100, "Solo", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton1()){
								sortir=1;
			}

		}
	}
	return sortir;
}

//Fonctions Background

void FOND_Espace(bool_e b){
	int x=0;
	int y=340;
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	if(b)
	{
		while (y>20){
			x=rand();
			ILI9341_DrawPixel(x,y,ILI9341_COLOR_WHITE);
			y--;
		}
	}
}

//Fonctions Detection

bool_e collision(uint16_t xc,uint16_t y,uint16_t r){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */

	uint32_t distance = sqrt(square((200-xc))+square((300-y)));		//à modifier
	if (distance<=(15)){


		return TRUE;

	}

	return FALSE;
}
//Fonctions	Buzzer

void buzzer(bool_e b)
{
	if(b)
	{
		writeBUZZER(1);

		HAL_Delay(500);			//test buzzer mais ça marche pas

		writeBUZZER(0);
	}
}

//Fonctions

int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);

	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	JOYSTICK_x_init();
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Portrait_2);
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_DrawCircle(120,20,5,ILI9341_COLOR_BLUE);
	//JOYSTICK_move_x();
	while (1){
		state_machine();
	}
}

void state_machine(void)
{
	int selM = 0;
	int selE = 0;
	bool_e j1 = FALSE;
	bool_e j2 = FALSE;

	typedef enum
	{
		INIT = 0,
		JOUEUR1,
		JOUEUR2,
		DEFAITE,
		VICTOIRE,
		MENU,
		OFF
	}state_e;
	static state_e state = INIT;

	switch(state)
	{
		case INIT:
						//initialiation du jeu écran titre

		selE = Ecran_titre_jeu();
		if(selE == 1)
			{
			state = MENU;
			}
		if(selE == -1)
			{
			state = OFF;
			}
		break;
		case MENU:
								//choix du nombre de joueurs

		selM = Ecran_Selection();
		if(selM == 1)
				{
			state = JOUEUR1;
				}
		if(selM == -1)
				{
			state = JOUEUR2;
				}
		break;
		case JOUEUR1:
						// 1 seul joueur
		//j1 = Mode_1_joueurs();
		if(j1){
			state = VICTOIRE;
			}
		state = DEFAITE;

		break;
		case JOUEUR2:
						// 2 joueurs

		//j2 = Mode_2_joueurs();
		if(j2)
			{
			state = VICTOIRE;
			}
		state = DEFAITE;

		break;
		case DEFAITE:
						//perd
		Ecran_defaite();
		state = MENU;
		break;
		case VICTOIRE:
						//gagne
		Ecran_victoire();
		state = MENU;
		break;
		default:
	break;
	}
}

