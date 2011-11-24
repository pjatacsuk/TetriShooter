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
	Coord coord;										// koordináták az ellenfélnek
	ALLEGRO_BITMAP* bmp;								//a bitmapja
	DeadAnim *deadanim;									// a dead animciók tárolása
	int type;											//ellenfél tipusa
	float speed;										//ellenfél sebessége
	int dead;											//hallot-e
	int ready_to_free;									//fel lehet-e szabaditani a memoriát
	int dead_counter;									//dead animációhoz szükséges számláló
} Enemy;



#endif