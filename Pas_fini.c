
//permet de faire afficher les ennemis et de les bouger dans un pattern prédéfini. Le code n'est pas fini je le reprendrais plus tard.

void AfficherEnnemi(int yEnnemi){
	int i=0;
	int16_t y;
	bool_e gauche=FALSE;
	bool_e droite=FALSE;
	static int xEnnemi=120;
	if (i!=10 && gauche==FALSE && droite==FALSE){
		ILI9341_DrawFilledCircle(xEnnemi,yEnnemi,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawFilledCircle(xEnnemi,yEnnemi-1,5,ILI9341_COLOR_BROWN);
		i++;
		y=yEnnemi;
	}
	if (i==10 && xEnnemi!=20 &&xEnnemi!=220){
		gauche=TRUE;
		i=0;
	}
	if (i==10 && xEnnemi==220){
		gauche=FALSE;
		droite=TRUE;
		i=0;
	}
	if (i==10 && xEnnemi==20){
		droite=FALSE;
		gauche=TRUE;
		i=0;
	}
	if (i==0 && xEnnemi==220){
		droite=FALSE;
		gauche=FALSE;
	}
	if (i==0 && xEnnemi==20){
		droite=FALSE;
		gauche=FALSE;
	}
	if (gauche){
		ILI9341_DrawFilledCircle(xEnnemi,y,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawFilledCircle(xEnnemi+1,y,5,ILI9341_COLOR_BROWN);
		xEnnemi++;
	}
	if(droite){
		ILI9341_DrawFilledCircle(xEnnemi,y,5,ILI9341_COLOR_BLACK);
		ILI9341_DrawFilledCircle(xEnnemi-1,y,5,ILI9341_COLOR_BROWN);
		xEnnemi--;
	}
}

//V2 de la fonction JOYSTICK_move_x() déjà dispo dans le fichier Code_joystick.c
void JOYSTICK_move_x(void){
	static int yEnnemi=321;
	while(1){
		while (JOYSTICK_x_getValue()>2200){
			JOYSTICK_move_x_GAUCHE();
			AfficherEnnemi(yEnnemi);
			yEnnemi--;
		}
		while(JOYSTICK_x_getValue()<1520){
			JOYSTICK__move_x_DROITE();
			AfficherEnnemi(yEnnemi);
			yEnnemi--;
		}
		AfficherEnnemi(yEnnemi);
		yEnnemi--;
	}
}
