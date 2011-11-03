#ifndef INC_SURPRISE_H
#define INC_SURPRISE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "_Resource.h"



typedef struct _Surprise {
	Coord coord;				//koordináták
	ALLEGRO_BITMAP *bmp;		//a surprise bitmapja
	int status;					//status-> elindult-e
	float speed;				//sebessége
	int dir;					//iránya
	ALLEGRO_SAMPLE* sample;		//hangja

} Surprise;

void NewSurprise(Surprise* surprise,char* path);
void UpdateSurprise(Surprise* surprise);
void FreeSurprise(Surprise* surprise);
void DrawSurprise(Surprise* surprise);

#endif