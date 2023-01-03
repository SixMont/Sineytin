(à mettre dans le header)
#if BLUEPILL
	#define LED_GREEN_GPIO		GPIOC
	#define LED_GREEN_PIN		GPIO_PIN_13
//___________________________________________________________________
	#define BUZZER_GPIO			GPIOA
	#define BUZZER_PIN			GPIO_PIN_8
//___________________________________________________________________
	#define BLUE_BUTTON_GPIO	GPIOA
	#define BLUE_BUTTON_PIN 	GPIO_PIN_15		//Pas de bouton sur la bluepill, choisissez le port souhait� si vous en reliez un.
#endif
