bool_e collision(uint16_t xc,uint16_t y,uint16_t r){


	/**
	 * détecte si la distance entre centre du cercle et centre du carré est inférieure
	 * au rayon du cercle et la moitié du côté du carré
	 */
	uint32_t distance = sqrt(square((200-xc))+square((300-y)));
	if (distance<=(15)){


		return TRUE;

	}

	return FALSE;
