#ifndef INC_ENEMY_H
#define INC_ENEMY_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "_Resource.h"
#include "_DeadAnim.h"

typedef struct _Enemy {
	Coord coord;										// koordin�t�k az ellenf�lnek
	ALLEGRO_BITMAP* bmp;								//a bitmapja
	DeadAnim *deadanim;									// a dead animci�k t�rol�sa
	int type;											//ellenf�l tipusa
	float speed;										//ellenf�l sebess�ge
	int dead;											//hallot-e
	int ready_to_free;									//fel lehet-e szabaditani a memori�t
	int dead_counter;									//dead anim�ci�hoz sz�ks�ges sz�ml�l�
} Enemy;



#endif