#ifndef INC_DEADANIM_H
#define INC_DEADANIM_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "_Resource.h"

typedef struct _DeadAnim {
		ALLEGRO_BITMAP* bmp[3]; // 3 bitmap a dead anim tárolására
		

} DeadAnim;



#endif