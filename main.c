#include <stdio.h>
#include <stdlib.h>
#include "_Game.h"
#include <allegro5\allegro.h>
#include "_Resource.h"
#include "_Menu.h"
typedef enum {MENU,GAME} state;
int main()
{
	state GameState;
		Game* MyGame;
		Menu* MyMenu;
	GameState = MENU;


	if(_InitAllegro()==0) // allegro init-je
	{
		while(STOP_GAME != 1)
		{
			switch(GameState)
			{
			case MENU:
				MyMenu = InitMenu();
				MenuLoop(MyMenu); //amig a menuben vagyunk a menu loopon belul fut a program
				FreeMenu(MyMenu);

				GameState = GAME;
				
				break;
			case GAME:
				MyGame = _InitGame("resource.txt"); // a játék initje
				_GameLoop(MyGame); //amig a jatek fut, a Game loopon belul fog az futni
				//	_FreeMyGame(MyGame); ez nem szuksegse, a game loop ugy lep ki, hogy felszabaditja
				GameState = MENU;
				break;
		
			}
		}
		
	}
	
	
	
		 // játék loop
	
	

	return 0;
}