#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include "_Resource.h"

typedef struct _Projectile {
	Coord coord;		//projectile koordinátái
	float speed;		//a projectile sebbesége
	int type;			//a projectile tipusa
	ALLEGRO_BITMAP* bmp;	//a projectile bitmapa
	bool shot;				//kilötték-e már
} Projectile;



#endif