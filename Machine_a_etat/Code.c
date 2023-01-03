void state_machine(void)
{
	typedef enum
	{
		INIT = 0,
		JOUEUR1,
		JOUEUR2,
		DEFAITE,
		VICTOIRE,
		MENU
	}state_e;
	static state_e state = INIT;
  
	switch(state)
	{
		case INIT:
						//initialiation du jeu écran titre
		state = MENU;
		break;
		case MENU:
								//choix du nombre de joueurs
		state = JOUEUR1;
		state = JOUEUR2;
		break;                   
		case JOUEUR1:
						// 1 seul joueur
		state = DEFAITE;
		state = VICTOIRE;
		break;
		case JOUEUR2:
						// 2 joueurs
		state = DEFAITE;
		state = VICTOIRE;
		break;
		case DEFAITE:
						//perd
		state = MENU;
		break;
		case VICTOIRE:
						//gagne
		state = MENU;
		break;
		default:
	break;
	}
}
