#include "_Surprise.h"
#include <string.h>


/** Az uj surprise létrehozása
* @param Surprise-ra mutató pointer, a surprise hoz szükséges utvonal (.png file) ami a bitmapja
* @return void -> nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/

void NewSurprise(Surprise* surprise,char* path)
{
	int rnd;
	char * pch;
	int i;
	int len;
	char sample_path[50] = {""};
	char *tmp;
	char* c = {"0"};
	srand((unsigned)time(0));
	
	if(surprise->bmp)
	{
		al_destroy_bitmap(surprise->bmp);
	}
	if(surprise->sample)
	{
 		al_destroy_sample(surprise->sample);
	}
	
	surprise->bmp = al_load_bitmap(path);
	CheckBitmap(surprise->bmp,path);

	
	
	//wav file betöltése
 	strcat(path,"\\");
 	tmp = strtok(path,"\\");
	tmp = strtok(NULL,"\\");
 	tmp = strtok(NULL,"\\");
	
	
	strcpy(sample_path,"data\\sounds\\");
	pch = strrchr(tmp,'.');
	len = pch - tmp + 1;
	c[0] = tmp[len-2];
	c[1] = '\0';
	surprise->dir = atoi(c);
	
	strncat(sample_path,tmp,len);
	
	
	strcat(sample_path,"wav");

  	surprise->sample = al_load_sample(sample_path);

	rnd = (rand()%600);
	if(surprise->dir == RIGHT)
	{
		surprise->coord.x = -(al_get_bitmap_width(surprise->bmp));
	}
	else
	if(surprise->dir == LEFT)
	{
		surprise->coord.x = SCREEN_W + al_get_bitmap_width(surprise->bmp);
	}
	if(rnd < al_get_bitmap_height(surprise->bmp))
	{
		surprise->coord.y = rnd + al_get_bitmap_height(surprise->bmp);
	}
	else if(rnd + al_get_bitmap_height(surprise->bmp) > SCREEN_H)
	{
		surprise->coord.y = rnd - al_get_bitmap_height(surprise->bmp);
	}
	else
	{
		surprise->coord.y = rnd;
	}
	surprise->speed = 5;

	surprise->status = 1;

	al_play_sample(surprise->sample,0.4,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL); //egyszeri lejátszás miatt
}


/** A surprise frissitése
* @param Surprise-ra mutató pointer
* @return void-> nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/
void UpdateSurprise(Surprise* surprise)
{
	if(surprise->status == 1)
	{
		
		if(surprise->dir == RIGHT)
		{
			if(surprise->coord.x < (SCREEN_W)+al_get_bitmap_width(surprise->bmp))
			{
				surprise->coord.x += surprise->speed;
			}
			else
			{
				surprise->status = 0;
			}
		}
		else if(surprise->dir == LEFT)
		{
			if(surprise->coord.x > -(al_get_bitmap_width(surprise->bmp)))
			{
				surprise->coord.x -= surprise->speed;
			}
			else
			{
				surprise->status = 0;
			}
		}
	}
}

/** A surprise memoria felszabaditasa
* @param Surprise-ra mutato pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/
void FreeSurprsie(Surprise* surprise)
{
	al_destroy_bitmap(surprise->bmp);
	free(surprise);

}
/** A surprsie kirajzólása
* @param Surprise-ra mutato pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/
void DrawSurprise(Surprise* surprise)
{
	if(surprise->bmp != 0)
	{
		al_draw_bitmap(surprise->bmp,surprise->coord.x,surprise->coord.y,0);
	}
}