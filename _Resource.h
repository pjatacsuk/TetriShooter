#ifndef INC_RESOURCE_H
#define INC_RESOURCE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

extern float FPS;			//fps nagysága
extern float SCREEN_H;		//screen magassága
extern float SCREEN_W;		//screen szélessége
extern int redraw;


extern enum Keys {UP,DOWN,LEFT,RIGHT,SPACE,SHIFT};		//billentyûk egyszerû kezelésére

typedef struct _Resource {
	
	char name[256];		//resource listához a nevek

} Resource;

typedef struct _Coord {
	float x,y;			//coordináták
} Coord;

float f_abs(float f);		//float absolut értékhez

int _own_random(int rnd);	//rand generator -> TODO


#endif