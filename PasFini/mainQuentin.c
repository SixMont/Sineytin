#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "stm32f1_adc.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "joystick.h"

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

static int xJoueur=120;
static int yJoueur=20;

//Diagramme d'etat
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

void Ecran_titre_jeu(void){
	FOND_Espace();
	ILI9341_Puts(55,100, "SINEYTIN", &Font_16x26, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
	ILI9341_Puts(95,200, "Start", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
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
// jusque la pour le diagramme d'état.
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

//Fonction affiche_ennemi à reimplémenter. Disponible dans github.

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

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);

	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);


		//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);
	JOYSTICK_x_init();
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	ILI9341_DrawCircle(120,20,5,ILI9341_COLOR_BLUE);
	JOYSTICK_move_x();

}
