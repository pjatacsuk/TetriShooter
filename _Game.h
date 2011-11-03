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
	ALLEGRO_DISPLAY *display;				//Allegro display-re mutató pointer, képernyõhöz kell
	ALLEGRO_EVENT_QUEUE *event_queue;		// az eventek kezeléséhez kell, allegro komponens
	ALLEGRO_TIMER *timer;					//allegro timer, szintén allegro komponens, az idõzítéshez kell
    ALLEGRO_FONT *font;						// allegro font ->betûtipus, szintén allegro komponens
	ALLEGRO_BITMAP* bg_foreground;			// a kétrészes háttér elölsû része
	ALLEGRO_BITMAP* bg_background;			// a kétrészes háttér hátsó része
	
	Resource *resource[80];					//a Resource-ok kezeléséhez egy tömb
	Enemy *enemy[10];						//az egyszerre 10 enemy tárolására lévõ tömb

	int GameResDB;							//resource -ok darabszáma

	int next_bgforeground_index;			//elülsõ háttér indexe
	int next_bgbackground_index;			//hátulsó háttér indexe
	int next_projectile_index;				//projectile indexe
	int enemy_down;							//meghalt enemy-k száma

	Player* player;							//a player struct-ra mutató pointer
	Surprise* surprise;					//a surprise struct-ra mutató pointer

	ALLEGRO_SAMPLE* death_sample;	//death animációhoz a hang

	int Keys[6];							//a lenyomadnó billentyûk kezelésére

	int MaxEnemy;							//A maximális enemy tipus száma
	int MaxBackGround;						//A maximális háttér tipus száma
	int MaxProjectile;						//A maximális lövedék tipus száma
	int MaxPlayerLife;						//A maximális PlayerLife tipus száma
	
	char *EnemyPath[MAX_PATH_COUNT];						//Enemy tipusuk bitmapjához utvonal
	char *DeadAnimPath[MAX_PATH_COUNT];					//Dead anim tipusok bitmapjához utvonal
	char *ProjectilePath[MAX_PATH_COUNT];				//projectile tipus bitmapjához utvonal
	char **(*BgPath);						//background tipusokhoz utvonal
	char *(*SurprisePath);					//a meglepikhez az útvonalak

	


	
	

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


void DeadAnimReader(Game *MyGame,char *dnm,int type); // a type megfelelõjû változoba olvassa be a *dnm szöveget
void DeadAnimLoader(Game *MyGame,int i,int type); // az i indexu enemybe tolti be a type tipusu anime-ot
char* DeadAnimCutter(Game *MyGame,int type); //a type tipusu animációt késziti elõ
void DrawDeadAnim(Game *MyGame,int i);		//A halálanimáció kirajzloása
void FreeDeadAnim(Enemy* enemy);



void GameBGLoad(Game *MyGame,int i);		//háttérbetöltése
#endif