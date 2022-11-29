

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
static void move(){
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
