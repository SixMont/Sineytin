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



void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton2(void)
{
	return !HAL_GPIO_ReadPin(BUTTON1_GPIO, BUTTON1_PIN);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BUTTON2_GPIO, BUTTON2_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}
static int xJoueur=120;
static int yJoueur=300;
static int xJoueur2=120;
static int yJoueur2=20;
uint16_t r=4;
static bool_e tir = FALSE;
static bool_e tir2 = FALSE;
static uint16_t y = 20;


/*static void move(){
	bool_e allerDroite=FALSE;
	bool_e allerGauche=FALSE;
	while(1){
		if (JOYSTICK_x_getValue()>2944){
			allerDroite=FALSE;
			allerGauche=TRUE;
		}else if (JOYSTICK_x_getValue()<1500){
			allerGauche=FALSE;
			allerDroite=TRUE;
		}else{
			allerGauche=FALSE;
			allerDroite=FALSE;
		}

		while (allerGauche){
			xJoueur++;
			ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
			ILI9341_DrawSquare(xJoueur+1,yJoueur,5,ILI9341_COLOR_BLUE);
			if (xJoueur==220){
				ILI9341_DrawSquare(xJoueur+1,yJoueur,5,ILI9341_COLOR_WHITE);
				allerGauche=FALSE;
				allerDroite=FALSE;
			}
		}
		while (allerDroite){
			xJoueur--;
			ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
			ILI9341_DrawSquare(xJoueur-1,yJoueur,5,ILI9341_COLOR_BLUE);
			if (xJoueur==20){
				ILI9341_DrawSquare(xJoueur-1,yJoueur,5,ILI9341_COLOR_WHITE);
				allerDroite=FALSE;
				allerGauche=FALSE;
			}
		}
	}

}*/

/*static void Test_Deplacement(){
	while(1)	//boucle de tâche de fond
		{
		if (JOYSTICK_x_getValue()>2200){
			while (xJoueur<220){
				ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
				ILI9341_DrawSquare(120,120,5,ILI9341_COLOR_WHITE);
				ILI9341_DrawSquare(xJoueur+10,yJoueur,5,ILI9341_COLOR_RED);
				xJoueur+=10;
				}
		}
		if (JOYSTICK_x_getValue()<1500){
			while (xJoueur>20){
				ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
				ILI9341_DrawSquare(120,120,5,ILI9341_COLOR_WHITE);
				ILI9341_DrawSquare(xJoueur-10,yJoueur,5,ILI9341_COLOR_BLUE);
				xJoueur-=10;
			}
		}

		if (JOYSTICK_x_getValue()<2200 && JOYSTICK_x_getValue()>1500){
				ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
				ILI9341_DrawSquare(120,120,5,ILI9341_COLOR_GREEN);
				xJoueur=120;
		}
	}
}*/

/*Fonction qui vas premettre de lancer l'écran titre
 * Fond étoiler
 * Titre du jeu
 * Bouton start
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

void Ecran_titre_jeu(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "SINEYTIN", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(95,280, "leave", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
}

void Ecran_Selection(void){
	FOND_Espace();
	ILI9341_Puts(65,100, "Mode Solo", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(45,200, "Mode 2 Joueurs", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	int i=0;
	while(1){

		if (JOYSTICK_y_getValue()>2200){
			i=1;
		}
		if(i==-1){
			ILI9341_Puts(65,100, "Mode Solo", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
			ILI9341_Puts(45,200, "Mode 2 Joueurs", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);
		}
		if (JOYSTICK_y_getValue()<1520){
			i=-1;
		}
		if (i==1){
			ILI9341_Puts(45,200, "Mode 2 Joueurs", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
			ILI9341_Puts(65,100, "Mode Solo", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);

		}
	}
}



void JOYSTICK_move_x(void){
	if (JOYSTICK_x_getValue()>2200){
		JOYSTICK__move_x_DROITE();
	}
	if (JOYSTICK_x_getValue()<1520){
		JOYSTICK_move_x_GAUCHE();
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


void JOYSTICK2_move_x(void){
	if (JOYSTICK2_x_getValue()<1000){
		JOYSTICK2_move_x_GAUCHE();
	}
	if (JOYSTICK2_x_getValue()>2200){
		JOYSTICK2_move_x_DROITE();
	}
}


void JOYSTICK2_move_x_DROITE(void){
	if (xJoueur2>20){
		ILI9341_DrawSquare(xJoueur2,yJoueur2,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur2-5,yJoueur2,5,ILI9341_COLOR_RED);
		xJoueur2-=5;
	}
}

void JOYSTICK2_move_x_GAUCHE(void){
	if (xJoueur2<220){
		ILI9341_DrawSquare(xJoueur2,yJoueur2,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawSquare(xJoueur2+5,yJoueur2,5,ILI9341_COLOR_RED);
		xJoueur2+=5;
	}
}


void drawLife(int nbLife, uint16_t color){
	for (int i=0; i<3 ; i++){
		ILI9341_DrawFilledRectangle(230, 230-i*100, 228,  270-i*100,ILI9341_COLOR_BLACK );
	}
	for (int i=0; i<nbLife ; i++){
		ILI9341_DrawFilledRectangle(230, 230-i*100, 228,  270-i*100,color);
	}
}

void drawLife2(int nbLife, uint16_t color){
	for (int i=0; i<3 ; i++){
		ILI9341_DrawFilledRectangle(10, 230-i*100, 20,  270-i*100,ILI9341_COLOR_BLACK );
	}
	for (int i=0; i<nbLife ; i++){
		ILI9341_DrawFilledRectangle(10, 230-i*100, 12,  270-i*100,color);
	}
}
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
//Fonction affiche_ennemi à reimplémenter. Disponible dans github.

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
	Mode_2_Joueurs();
}
