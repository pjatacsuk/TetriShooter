#ifndef INC_PROJECTILE_H
#define INC_PROJECTILE_H

#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include "_Resource.h"

typedef struct _Projectile {
	Coord coord;									//projectile koordin�t�i
	float speed;									//a projectile sebbes�ge
	int type;										//a projectile tipusa
	ALLEGRO_BITMAP* bmp;							//a projectile bitmapja
	bool shot;										//kil�tt�k-e m�r
	struct _Projectile* kovetkezo;					//a kovetkezo projectile ra mutato pointer
	struct _Projectile* elozo;						//az elozo projectile ra mutato pointer
} Projectile;

typedef struct _ProjectileList {
	Projectile* eleje;								//a projectile list elejere mutato pointer
	Projectile* vege;								//a projectile list vegere mutato pointer

} ProjectileList;

#endif