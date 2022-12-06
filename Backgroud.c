
*/
permet de créée un background représentant l'espace (attention pa fini)
@brief
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
