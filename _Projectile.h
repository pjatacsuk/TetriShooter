#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include "_Resource.h"

typedef struct _Projectile {
	Coord coord;		//projectile koordin�t�i
	float speed;		//a projectile sebbes�ge
	int type;			//a projectile tipusa
	ALLEGRO_BITMAP* bmp;	//a projectile bitmapa
	bool shot;				//kil�tt�k-e m�r
} Projectile;



#endif