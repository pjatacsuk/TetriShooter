#ifndef INC_MENU_H
#define INC_MENU_H
#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include "_Resource.h"

enum allapot {alap,newgame,quit} all;

typedef struct _Menu {
	ALLEGRO_BITMAP* bg;						//a menu hattere bitmap
	ALLEGRO_FONT* font;						//a menuben hasznalt font

	ALLEGRO_DISPLAY *display;				//Allegro display-re mutató pointer, képernyõhöz kell
	ALLEGRO_EVENT_QUEUE *event_queue;		// az eventek kezeléséhez kell, allegro komponens
	ALLEGRO_TIMER *timer;					//allegro timer, szintén allegro komponens, az idõzítéshez kell


} Menu;



Menu* InitMenu();
Menu* MallocMenu();
void MenuLoop(Menu* MyMenu);
void FreeMenu(Menu* MyMenu);
#endif