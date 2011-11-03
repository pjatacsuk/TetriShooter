#include <stdio.h>
#include <stdlib.h>
#include "_Game.h"
#include <allegro5\allegro.h>
#include "_Resource.h"
int main()
{
	Game* MyGame;

	if(_InitAllegro()==0) // allegro init-je
	{
		MyGame = _InitGame("resource.txt"); // a játék initje
	}
		_GameLoop(MyGame); // játék loop
	
	

	return 0;
}