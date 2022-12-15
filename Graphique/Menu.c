
//fonctions ecran d'acceuil

//fonctions ecran selection

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
			ILI9341_Puts(45,200, "Mode 2 Joueurs", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);
			HAL_Delay(50);
			ILI9341_Puts(45,200, "Mode 2 Joueurs", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
		}
		if (JOYSTICK_y_getValue()<1520){
			i=-1;
		}
		if (i==1){
			ILI9341_Puts(65,100, "Mode Solo", &Font_11x18, ILI9341_COLOR_BLACK,ILI9341_COLOR_WHITE);
			HAL_Delay(200);
			ILI9341_Puts(65,100, "Mode Solo", &Font_11x18, ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
		}
	}
}
