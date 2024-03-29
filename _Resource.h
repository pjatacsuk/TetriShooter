#ifndef INC_RESOURCE_H
#define INC_RESOURCE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

extern float FPS;										//fps nagys�ga
extern float SCREEN_H;									//screen magass�ga
extern float SCREEN_W;									//screen sz�less�ge
extern int redraw;
extern int STOP_GAME;									// a game futas addig tart amig nem true

extern enum Keys {UP,DOWN,LEFT,RIGHT,SPACE,SHIFT};		//billenty�k egyszer� kezel�s�re

typedef struct _Resource {
	
	char name[256];										//resource list�hoz a nevek

} Resource;

typedef struct _Coord {
	float x,y;											//coordin�t�k
} Coord;

float f_abs(float f);									//float absolut �rt�khez

void CheckBitmap(ALLEGRO_BITMAP* bmp,char* path);		//bitmapok ellenorzeserevan

int _own_random(int rnd);								//rand generator -> TODO - nem lesz a kozeljovoben


#endif