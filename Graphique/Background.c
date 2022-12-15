
/*
permet de créée un background représentant l'espace (attention pa fini)
@brief
@Param boolean b : true pour le mode menu et false pour le mode jeu
*/
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
