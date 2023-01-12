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
#include "stm32f1_adc.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "joystick.h"
#include <math.h>

#define square(a) (a)*(a)

static volatile uint32_t t = 0;
static int xJoueur=120;
static int yJoueur=300;
static int xJoueur2=120;
static int yJoueur2=20;
uint16_t r=4;
static bool_e tir = FALSE;
static bool_e tir2 = FALSE;
static uint16_t y = 20;

void process_ms(void)
{
	if(t)
		t--;
}

/*
 * @Brief modifie la valeur du
 * @param  Non
 * @retval Non
*/
/*
void writeBUZZER(bool_e b)
{
	!HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, b);
}
*/
/*
 * @Brief lit la valeur du bouton2
 * @param  Non
 * @retval Non
*/

bool_e readButton2(void)
{
	return !HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN);
}

/*
 * @Brief lit la valeur du bouton
 * @param  Non
 * @retval Non
*/

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN);
}

/*
 * @Brief detecte les mouvements du joystick
 * @param  Non
 * @retval Non
*/

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

/*
 * @Brief decale un carré vers la droite
 * @param  Non
 * @retval Non
*/

void JOYSTICK__move_x_DROITE(void){
	if (xJoueur>20){
		ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur-5,yJoueur,5,ILI9341_COLOR_BLUE);
		xJoueur-=5;
	}
}

/*
 * @Brief decale un carré vers la gauche
 * @param  Non
 * @retval Non
*/

void JOYSTICK_move_x_GAUCHE(void){
	if (xJoueur<220){
		ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur+5,yJoueur,5,ILI9341_COLOR_BLUE);
		xJoueur+=5;
	}
}

/*
 * @Brief detecte les mouvements du joystick2
 * @param  Non
 * @retval Non
*/

void JOYSTICK2_move_x(void){
	if (JOYSTICK2_x_getValue()<1000){
		JOYSTICK2_move_x_GAUCHE();
	}
	if (JOYSTICK2_x_getValue()>2200){
		JOYSTICK2_move_x_DROITE();
	}
}

/*
 * @Brief decale un carré vers la droite
 * @param  Non
 * @retval Non
*/

void JOYSTICK2_move_x_DROITE(void){
	if (xJoueur2>20){
		ILI9341_DrawSquare(xJoueur2,yJoueur2,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur2-5,yJoueur2,5,ILI9341_COLOR_RED);
		xJoueur2-=5;
	}
}

/*
 * @Brief decale un carré vers la gauche
 * @param  Non
 * @retval Non
*/

void JOYSTICK2_move_x_GAUCHE(void){
	if (xJoueur2<220){
		ILI9341_DrawSquare(xJoueur2,yJoueur2,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur2+5,yJoueur2,5,ILI9341_COLOR_RED);
		xJoueur2+=5;
	}
}

/*
 * @Brief affiche l'ecran de defaite
 * @param  Non
 * @retval Non
*/

void Ecran_defaite(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "GAME OVER", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_RED);
	ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int sortir=0;

		while(sortir==0){

			ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton()){
				sortir=1;

			}
		}
}

/*
 * @Brief affiche l'ecran de victoire
 * @param  Non
 * @retval Non
*/

void Ecran_victoire(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "SUCCESS", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_GREEN);
	ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int sortir=0;

		while(sortir==0){

			ILI9341_Puts(95,200, "Restart", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton()){
				sortir=1;

			}
		}
}

/*
 * @Brief affiche l'ecran titre
 * @param  Non
 * @retval entier 1 => leave -1 => Start
*/

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

				if(readButton()){
					sortir=-1;
				}
			}

			if (JOYSTICK_y_getValue()<1520){
				entrer=-1;
			}
			if (entrer==1){ //mode start
				ILI9341_Puts(95,280, "leave", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
				ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

				if(readButton()){
					sortir=1;
				}
			}
		}
		return sortir;
}

/*
 * @Brief affiche l'ecran de selection de joueurs
 * @param  Non
 * @retval entier 1 => 2 joueurs -1 => solo
*/

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
			if(readButton()){
											sortir=-1;
			}
		}
		if (JOYSTICK_y_getValue()<1520){
			i=-1;
		}
		if (i==1){//mode solo
			ILI9341_Puts(45,200, "2 players", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
			ILI9341_Puts(65,100, "Solo", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

			if(readButton()){
								sortir=1;
			}

		}
	}
	return sortir;
}

/*
 * @Brief affiche le fond d'ecran
 * @param  Non
 * @retval Non
*/

void FOND_Espace(void){
	int x=0;
	int y=340;
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	while (y>20){
		x=rand();
		ILI9341_DrawPixel(x,y,ILI9341_COLOR_WHITE);
		y--;

	}
}

/*
 * @Brief affiche le fond d'ecran
 * @param  x : coordonnée x centre boule y : coordonnée y centre boule
 * @retval TRUE : si collision FALSE : si pas collision
*/

bool_e collision(uint32_t xc,uint32_t y,uint32_t r){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */
	uint32_t distance = sqrt(square((xJoueur2-xc))+square((yJoueur2-y)));
	if (distance<=(r+4)){


		return TRUE;

	}

	return FALSE;

}
bool_e collision2(uint32_t xc,uint32_t y,uint32_t r){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */
	uint32_t distance = sqrt(square((xJoueur-xc))+square((yJoueur-y)));
	if (distance<=(r+4)){


		return TRUE;

	}

	return FALSE;

}
void shot(uint16_t xc, uint16_t y){
	ILI9341_DrawFilledCircle(xc, y+4,r, ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledCircle(xc, y-2,r, ILI9341_COLOR_RED);
}

void shot2(uint16_t xc, uint16_t y){
	ILI9341_DrawFilledCircle(xc, y-4,r, ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledCircle(xc, y+2,r, ILI9341_COLOR_RED);
}

/*
 * @Brief mode deux joueurs, chaqu'un controle un personnage
 * @param  Non
 * @retval TRUE pour victoire et FALSE pour defaite
*/

bool_e Mode_2_Joueurs(void){
	uint32_t xc;
	uint32_t xc2;
	uint32_t y;
	y=yJoueur;
	uint32_t y2=yJoueur2;
	int life1=3;
	int life2=3;
	int life1Before=3;
	int life2Before=3;
	drawLife(life1,ILI9341_COLOR_BLUE);
	drawLife2(life1,ILI9341_COLOR_RED);
	while (life1!=0 && life2!= 0){
		JOYSTICK_move_x();
		JOYSTICK2_move_x();
		if(readButton() || tir==TRUE ){
			if(tir==FALSE){
				xc=xJoueur;
				tir=TRUE;
			}
			shot(xc,y);
			if(y<=20){
				tir=FALSE;
				ILI9341_DrawFilledCircle(xc, y+2,r+2, ILI9341_COLOR_BLACK);
				y=yJoueur;
				}
				if (collision(xc,y,10)){
					tir=FALSE;
					y=yJoueur;
					life2--;
				}
				if (life2<life2Before){
					drawLife2(life2,ILI9341_COLOR_RED);
					life2Before=life2;
				}
				y--;
		}
		if(readButton2() || tir2==TRUE ){
					if(tir2==FALSE){
						xc2=xJoueur2;
						tir2=TRUE;
					}
					shot2(xc2,y2);
					if(y2>=310){
						tir2=FALSE;
						ILI9341_DrawFilledCircle(xc2, y2+2,r+2, ILI9341_COLOR_BLACK);
						y2=yJoueur2;
						}
						if (collision2(xc2,y2,10)){
							tir2=FALSE;
							life1--;
							y2=yJoueur2;
						}
						if (life1<life1Before){
							drawLife(life1,ILI9341_COLOR_BLUE);
							life1Before=life1;
						}
						y2++;
				}
	}
	if (life1==0){
		return TRUE;
	}
	if (life2==0){
		return FALSE;
	}
}

/*
 * @Brief affiche les vies d'un cote de l'ecran
 * @param entier : nombre de vies entier : couleur
 * @retval Non
*/

void drawLife(int nbLife, uint16_t color){
	for (int i=0; i<3 ; i++){
		ILI9341_DrawFilledRectangle(230, 230-i*100, 228,  270-i*100,ILI9341_COLOR_BLACK );
	}
	for (int i=0; i<nbLife ; i++){
		ILI9341_DrawFilledRectangle(230, 230-i*100, 228,  270-i*100,color);
	}
}

/*
 * @Brief affiche les vies d'un cote de l'ecran
 * @param entier : nombre de vies entier : couleur
 * @retval Non
*/

void drawLife2(int nbLife, uint16_t color){
	for (int i=0; i<3 ; i++){
		ILI9341_DrawFilledRectangle(10, 230-i*100, 20,  270-i*100,ILI9341_COLOR_BLACK );
	}
	for (int i=0; i<nbLife ; i++){
		ILI9341_DrawFilledRectangle(10, 230-i*100, 12,  270-i*100,color);
	}
}

int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	//UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	//SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);

	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);


		//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);
	JOYSTICK_x_init();
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Portrait_2);
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	//Ecran_titre_jeu();
	//Ecran_Selection();
	//JOYSTICK2_move_x();
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
		FOND_Espace();
		j2 = Mode_2_Joueurs();
		if(j2)
			{
			state = VICTOIRE;
			}
		else
			{
			state = DEFAITE;
			}

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

		case OFF:
		ILI9341_DisplayOff();
		break;

		default:
	break;
	}
}
