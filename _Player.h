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
	Coord coord;		//koordin�t�k
	float speed;		//a j�t�kos sebess�ge
	Projectile *projectile[4]; // a n�gy l�ved�k t�mbje
	int life_left;				//a h�tral�v� �letek sz�ma
	ALLEGRO_BITMAP *bmp[5];		//a player h�tral�v� �leteihez igazitott bitmapok
	ALLEGRO_SAMPLE* sample;	//a l�v�shez a hang
	ALLEGRO_SAMPLE* boost;	//a boost-hoz a hang
} Player;


bool ColDetect(int key,Player* player);
void UpdatePlayer(Player* player,int Keys[5]);



#endif