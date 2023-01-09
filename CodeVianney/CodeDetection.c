static uint16_t yEnnemi = 240;
static uint16_t xEnnemi = 240;
uint16_t r=4;
static bool_e tir = FALSE;
static uint16_t y = 20;





void shot(uint16_t xc, uint16_t y){





	ILI9341_DrawFilledCircle(xc, y-4,r, ILI9341_COLOR_WHITE);
	//HAL_Delay(5);
	ILI9341_DrawFilledCircle(xc, y+2,r, ILI9341_COLOR_RED);

}



bool_e collision(uint16_t xc,uint16_t y,uint16_t r){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */
	uint32_t distance = sqrt(square((xEnnemi-xc))+square((yEnnemi-y)));
	if (distance<=(r+4)){


		return TRUE;

	}

	return FALSE;

}


int main(void)
{

			if(readButton() || tir==TRUE ){

			if(tir==FALSE){
				xc=xJoueur;
				tir=TRUE;


			}


			shot(xc,y);

			if(y>=310){

				tir=FALSE;

				ILI9341_DrawFilledCircle(xc, y+2,r+2, ILI9341_COLOR_WHITE);
				y=20;
			}



			if(collision(xc,y,10)){


				ILI9341_DrawFilledRectangle(xEnnemi-5,yEnnemi-5,xEnnemi+2,yEnnemi+2,ILI9341_COLOR_WHITE);
				ILI9341_DrawFilledCircle(xc, y+2,r+2, ILI9341_COLOR_WHITE);
				tir=FALSE;
				y=20;
			}
			y++;

			}
