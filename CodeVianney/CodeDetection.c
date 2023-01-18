#include <stdlib.h>
#include <time.h>



#define square(a) (a)*(a)

static uint16_t xJoueur = 120;
static uint16_t yJoueur = 20;

//Coordonnées du CENTRE du carré ennemi
uint16_t r=4;
static bool_e tir = FALSE;
static uint16_t y = 20;
static uint16_t disparition = 0;
static uint8_t score = 0;
static uint16_t vie = 0;



typedef struct
{
	uint16_t mvt;
	uint16_t x;
	uint16_t y;
	bool_e actif;
}ennemi;

static uint16_t millis = 0;

static ennemi tabEnnemi[4];

void ennemi_init(){

	tabEnnemi[0].mvt = 800;
	tabEnnemi[0].x = 55;
	tabEnnemi[0].y = 240;
	tabEnnemi[0].actif=TRUE;

	tabEnnemi[1].mvt = 800;
	tabEnnemi[1].x = 70;
	tabEnnemi[1].y = 240;
	tabEnnemi[1].actif=FALSE;

	tabEnnemi[2].mvt = 800;
	tabEnnemi[2].x = 80;
	tabEnnemi[2].y = 240;
	tabEnnemi[2].actif=FALSE;

	tabEnnemi[3].mvt = 800;
	tabEnnemi[3].x = 100;
	tabEnnemi[3].y = 240;
	tabEnnemi[3].actif=FALSE;


}

static void process_ms(void){

	static volatile uint32_t t = 99999999;

	if(t){
		t--;
	}

	millis++;

}



void AvanceEnnemiBas(uint16_t xEnnemi,uint16_t yEnnemi){


	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-5),(uint16_t)(yEnnemi-4),(uint16_t)(xEnnemi+3),(uint16_t)(yEnnemi+4),ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-5),(uint16_t)(yEnnemi-5),(uint16_t)(xEnnemi+3),(uint16_t)(yEnnemi+3),ILI9341_COLOR_BLUE);

	}

void AvanceEnnemiDroite(uint16_t xEnnemi,uint16_t yEnnemi){



	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-4),(uint16_t)(yEnnemi-4),(uint16_t)(xEnnemi+4),(uint16_t)(yEnnemi+4),ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-5),(uint16_t)(yEnnemi-5),(uint16_t)(xEnnemi+3),(uint16_t)(yEnnemi+3),ILI9341_COLOR_BLUE);


}


void AvanceEnnemiGauche(uint16_t xEnnemi,uint16_t yEnnemi){

	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-6),(uint16_t)(yEnnemi-4),(uint16_t)(xEnnemi+2),(uint16_t)(yEnnemi+4),ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledRectangle((uint16_t)(xEnnemi-5),(uint16_t)(yEnnemi-5),(uint16_t)(xEnnemi+3),(uint16_t)(yEnnemi+3),ILI9341_COLOR_BLUE);

}

void JOYSTICK__move_x_DROITE(void){

	if (xJoueur>20){
		ILI9341_DrawFilledRectangle(xJoueur, yJoueur, xJoueur+10, yJoueur+10, ILI9341_COLOR_BLACK);
		ILI9341_DrawFilledRectangle(xJoueur-5, yJoueur, xJoueur+5, yJoueur+10, ILI9341_COLOR_YELLOW);
		xJoueur-=5;
	}
}

void JOYSTICK_move_x_GAUCHE(void){

	if (xJoueur<220){
		ILI9341_DrawFilledRectangle(xJoueur, yJoueur, xJoueur+10, yJoueur+10, ILI9341_COLOR_BLACK);
		ILI9341_DrawFilledRectangle(xJoueur+5, yJoueur, xJoueur+15, yJoueur+10, ILI9341_COLOR_YELLOW);
		xJoueur+=5;
	}
}





/**
 * Cette fonction gère le trajet des ennemis sur l'écran
 */



void affich_ennemi(uint8_t nb){
	//static uint16_t mvt=800;

	tabEnnemi[nb].mvt--;
	uint16_t mouvement = tabEnnemi[nb].mvt;

	if(tabEnnemi[nb].actif){

		if (mouvement > 770){

			AvanceEnnemiBas(tabEnnemi[nb].x,tabEnnemi[nb].y);
			tabEnnemi[nb].y--;
		}

		if(mouvement>=740 && mouvement<=770){

			AvanceEnnemiDroite(tabEnnemi[nb].x,tabEnnemi[nb].y);
			tabEnnemi[nb].y--;
			tabEnnemi[nb].x--;
		}

		if(mouvement<=740 && mouvement>650){

			AvanceEnnemiGauche(tabEnnemi[nb].x,tabEnnemi[nb].y);
			tabEnnemi[nb].y--;
			tabEnnemi[nb].x++;
		}

		if (mouvement<=650 && mouvement >500){

			AvanceEnnemiBas(tabEnnemi[nb].x,tabEnnemi[nb].y);
			tabEnnemi[nb].y--;
		}


	}


		if (tabEnnemi[nb].y<20 && tabEnnemi[nb].actif == TRUE){

			ILI9341_DrawFilledRectangle(tabEnnemi[nb].x-6,tabEnnemi[nb].y-4,tabEnnemi[nb].x+3,tabEnnemi[nb].y+4,ILI9341_COLOR_BLACK);
			tabEnnemi[nb].x=240;
			tabEnnemi[nb].y=240;
			tabEnnemi[nb].mvt=0;
			tabEnnemi[nb].actif=FALSE;
			tabEnnemi[nb+1].actif=TRUE;
			disparition ++;
			vie--;
		}

	}


bool_e collision(uint16_t xc,uint16_t y,uint16_t r, uint8_t i){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */
	double distance = sqrt(square((tabEnnemi[i].x-xc))+square((tabEnnemi[i].y-y)));
	if (distance<=(r+4)){



		return TRUE;

	}

	return FALSE;

}

void Mode2Joueurs(void){
	FOND_Espace();
	ennemi_init();
	Systick_add_callback_function(&process_ms);




	//uint16_t timer = 100;
	static uint16_t xc;
	ILI9341_DrawFilledRectangle(xJoueur, yJoueur, (uint16_t) xJoueur+10, (uint16_t) yJoueur+10, ILI9341_COLOR_BLACK);
	//ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_BLACK);


	while(1)
	{

		if (millis >= 15)
		{
			millis = 0;
			if (JOYSTICK_x_getValue()>2200){
						JOYSTICK_move_x_GAUCHE();
					}
					if(JOYSTICK_x_getValue()<1520){
						JOYSTICK__move_x_DROITE();
					}


					for(uint8_t i = 0;i<=3;i++){

						if(tabEnnemi[i].actif==TRUE){

							affich_ennemi(i);
							if(collision(xc,y,10,i)){


											ILI9341_DrawFilledRectangle(tabEnnemi[i].x-6,tabEnnemi[i].y-4,tabEnnemi[i].x+3,tabEnnemi[i].y+4,ILI9341_COLOR_BLACK);
											ILI9341_DrawFilledCircle(xc, y+2,r+2, ILI9341_COLOR_BLACK);
											tir=FALSE;
											tabEnnemi[i].actif=FALSE;
											tabEnnemi[i+1].actif=TRUE;
											y=20;
											disparition ++;
											char variable_string[5];
											//ILI9341_Rotate(ILI9341_Orientation_Portrait_1);
											score++;
											//sprintf(variable_string, "%d", score);
											//ILI9341_Puts(300,200, variable_string, &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
										}

						}

						if(disparition == 4){
							disparition = 0;
							ennemi_init();
						}

					}



					if(readButton() || tir==TRUE ){

						if(tir==FALSE){
							xc=xJoueur;
							tir=TRUE;
						}


						shot(xc,y);

						if(y>=310){

							tir=FALSE;
							ILI9341_DrawFilledCircle(xc, y+2,r+2, ILI9341_COLOR_BLACK);
							y=20;
						}

						y+=3;

					}
		}

		//HAL_Delay(15);



	}
