#ifndef INC_PLAYER_H
#define INC_PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include <stdlib.h>
#include "_Resource.h"
#include "_Projectile.h"


typedef struct _Player {
	Coord coord;		//koordináták
	float speed;		//a játékos sebessége
	Projectile *projectile[4]; // a négy lövedék tömbje
	int life_left;				//a hátralévõ életek száma
	ALLEGRO_BITMAP *bmp[5];		//a player hátralévõ életeihez igazitott bitmapok
	ALLEGRO_SAMPLE* sample;	//a lövéshez a hang
	ALLEGRO_SAMPLE* boost;	//a boost-hoz a hang
} Player;


bool ColDetect(int key,Player* player);
void UpdatePlayer(Player* player,int Keys[5]);



#endif