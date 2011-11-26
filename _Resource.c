

#include "_Resource.h"
#include <stdio.h>

float FPS = 60; //fixalt globalis valtozo
float  SCREEN_W = 600; //fixalt glob valt
float  SCREEN_H = 750; //fix glob valt
int redraw;  // a GameLoop mukodesehez kell, ha 1 akkor kell ujra rajzolni
int STOP_GAME = 0;

/** Sajat float abszolut ertek szamitas
* @param float valtozo
* @return float valtozo, abszolut ertekesen
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
float f_abs(float f)
{
	if(f >= 0.0000000000000000001)
	{
		return f;
	}
	else
	{
		return f*-1;
	}

}
/** A bitmapok betoltesenek sikeresseget vizsgalja, ha nem sikerult betolteni a bitmapot akkor kilep a program
* @param a Bitmapra mutato pinter, a bitmap path-ja
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.11.25
*/
void CheckBitmap(ALLEGRO_BITMAP* bmp,char* path)
{
	if(bmp == NULL)
	{
		STOP_GAME = 1; //leall a jatek mivel nem sikerult betolteni a bitmapop
		
		printf("Nincs meg a kovetkezo bitmap %s \n",path);
		
	}
	
}