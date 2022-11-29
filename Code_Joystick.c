

//Dessin de carre
//a mettre dans le fichier stm32f1_ili9341.c

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
