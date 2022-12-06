

/*Dessin de carre
a mettre dans le fichier stm32f1_ili9341.c
@brief
@param 
*/
void ILI9341_DrawSquare(int16_t x0, int16_t y0, int16_t taille, uint16_t color){ //x0 et y0 coresponde au centre du carré
	for(int i=0; i<5;i++){
		ILI9341_DrawLine(x0+taille/2+i,y0,x0+taille/2+i,y0+taille/2+i,color); // On dessine la moitiée du coté gauche
		ILI9341_DrawLine(x0+taille/2+i,y0,x0+taille/2+i,y0-taille/2-i,color); // On dessine l'autre moitiée du coté gauche
		ILI9341_DrawLine(x0-taille/2-i,y0,x0-taille/2-i,y0+taille/2+i,color);
		ILI9341_DrawLine(x0-taille/2-i,y0,x0-taille/2-i,y0-taille/2-i,color);
		ILI9341_DrawLine(x0,y0+taille/2+i,x0+taille/2+i,y0+taille/2+i,color);
		ILI9341_DrawLine(x0,y0+taille/2+i,x0-taille/2-i,y0+taille/2+i,color);
		ILI9341_DrawLine(x0,y0-taille/2-i,x0+taille/2+i,y0-taille/2-i,color);
		ILI9341_DrawLine(x0,y0-taille/2-i,x0-taille/2-i,y0-taille/2-i,color);

	}
}

/*
Fonction test qui permet de faire bouger un caree de gauche a droite sans s'arrêter
@breif 
*/
static void move_test(){
	static int xJoueur=120;
	static int yJoueur=20;
	bool_e allerDroite=FALSE;
	bool_e allerGauche=TRUE;
	while(1){
		while (allerGauche){
			xJoueur++;
			ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
			ILI9341_DrawSquare(xJoueur+1,yJoueur,5,ILI9341_COLOR_BLUE);
			if (xJoueur==220){
				ILI9341_DrawSquare(xJoueur+1,yJoueur,5,ILI9341_COLOR_WHITE);
				allerGauche=FALSE;
				allerDroite=TRUE;
			}
		}
		while (allerDroite){
			xJoueur--;
			ILI9341_DrawSquare(xJoueur,yJoueur,5,ILI9341_COLOR_WHITE);
			ILI9341_DrawSquare(xJoueur-1,yJoueur,5,ILI9341_COLOR_BLUE);
			if (xJoueur==20){
				ILI9341_DrawSquare(xJoueur-1,yJoueur,5,ILI9341_COLOR_WHITE);
				allerDroite=FALSE;
				allerGauche=TRUE;
			}
		}
	}

}

/*Fonction qui permet de faire bouger le carré corectement avec le joystick
@brief
*/
void JOYSTICK_move_x(void){
	while(1){
		while (JOYSTICK_x_getValue()>2200){
			JOYSTICK_move_x_GAUCHE();
		}
		while(JOYSTICK_x_getValue()<1520){
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
