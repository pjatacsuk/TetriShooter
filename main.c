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
		MyGame = _InitGame("resource.txt"); // a j�t�k initje
	}
		_GameLoop(MyGame); // j�t�k loop
	
	

	return 0;
}