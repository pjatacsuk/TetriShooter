#ifndef INC_GAME_H
#define INC_GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "_Resource.h"
#include "_Player.h"
#include "_Enemy.h"
#include "_Surprise.h"

#define MaxResourceDB 80;
#define MAX_PATH_COUNT 5




typedef char * string;

typedef struct _Game {
	ALLEGRO_DISPLAY *display;				//Allegro display-re mutat� pointer, k�perny�h�z kell
	ALLEGRO_EVENT_QUEUE *event_queue;		// az eventek kezel�s�hez kell, allegro komponens
	ALLEGRO_TIMER *timer;					//allegro timer, szint�n allegro komponens, az id�z�t�shez kell
    ALLEGRO_FONT *font;						// allegro font ->bet�tipus, szint�n allegro komponens
	ALLEGRO_BITMAP* bg_foreground;			// a k�tr�szes h�tt�r el�ls� r�sze
	ALLEGRO_BITMAP* bg_background;			// a k�tr�szes h�tt�r h�ts� r�sze
	
	Resource *resource[80];					//a Resource-ok kezel�s�hez egy t�mb
	Enemy *enemy[10];						//az egyszerre 10 enemy t�rol�s�ra l�v� t�mb

	int GameResDB;							//resource -ok darabsz�ma

	int next_bgforeground_index;			//el�ls� h�tt�r indexe
	int next_bgbackground_index;			//h�tuls� h�tt�r indexe
	int next_projectile_index;				//projectile indexe
	int enemy_down;							//meghalt enemy-k sz�ma

	Player* player;							//a player struct-ra mutat� pointer
	Surprise* surprise;					//a surprise struct-ra mutat� pointer

	ALLEGRO_SAMPLE* death_sample;	//death anim�ci�hoz a hang

	int Keys[6];							//a lenyomadn� billenty�k kezel�s�re

	int MaxEnemy;							//A maxim�lis enemy tipus sz�ma
	int MaxBackGround;						//A maxim�lis h�tt�r tipus sz�ma
	int MaxProjectile;						//A maxim�lis l�ved�k tipus sz�ma
	int MaxPlayerLife;						//A maxim�lis PlayerLife tipus sz�ma
	
	char *EnemyPath[MAX_PATH_COUNT];						//Enemy tipusuk bitmapj�hoz utvonal
	char *DeadAnimPath[MAX_PATH_COUNT];					//Dead anim tipusok bitmapj�hoz utvonal
	char *ProjectilePath[MAX_PATH_COUNT];				//projectile tipus bitmapj�hoz utvonal
	char **(*BgPath);						//background tipusokhoz utvonal
	char *(*SurprisePath);					//a meglepikhez az �tvonalak

	


	
	

} Game;

bool _InitAllegro();		
void _GameResourceReader(Game *MyGame,char *file_path);
Game* _InitGame(char* file_path);

bool _GameLoop(Game *MyGame);

Game* _MallocMyGame();
void _FreeMyGame(Game *MyGame);

void Draw(Game *MyGame);

void DrawPlayer(Game *MyGame);

void UpdateProjectile(Game *MyGame);
void DrawProjectile(Game *MyGame);
void FreeProjectile(Projectile *projectile);
void NewProjectile(Game *MyGame,int i);

void NewEnemy(Game* MyGame,int i);
void FreeEnemy(Enemy *enemy);
void UpdateEnemy(Game *MyGame);
void DrawEnemy(Game *MyGame);


void DeadAnimReader(Game *MyGame,char *dnm,int type); // a type megfelel�j� v�ltozoba olvassa be a *dnm sz�veget
void DeadAnimLoader(Game *MyGame,int i,int type); // az i indexu enemybe tolti be a type tipusu anime-ot
char* DeadAnimCutter(Game *MyGame,int type); //a type tipusu anim�ci�t k�sziti el�
void DrawDeadAnim(Game *MyGame,int i);		//A hal�lanim�ci� kirajzlo�sa
void FreeDeadAnim(Enemy* enemy);



void GameBGLoad(Game *MyGame,int i);		//h�tt�rbet�lt�se
#endif