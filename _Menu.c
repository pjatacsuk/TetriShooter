#include "_Menu.h"


/** A Menu mallocalasa
* @param Nincs
* @return a Menu-re mutato pointer
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
Menu* MallocMenu()
{
	
	Menu* MyMenu = (Menu*)malloc(sizeof(Menu));
}
/** A Menu inicializalasas
* @param Nincs
* @return a Menu-re mutato pointer
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
Menu* InitMenu()
{
	Menu* MyMenu = MallocMenu();
	
	
	MyMenu->timer= al_create_timer(1.0 / FPS);

	   if(!MyMenu->timer) 
	   {
		 printf("failed to create timer!\n");
		  return 0;
	   }

	   //display kreálása
   
	   MyMenu->display = al_create_display(SCREEN_W,SCREEN_H);
	   if(!MyMenu->display) 
	   {
		  fprintf(stderr, "failed to create display!\n");
		  al_destroy_timer(MyMenu->timer);
		  return 0;
	   } 

	   //event queue kreálása

	  MyMenu->event_queue = al_create_event_queue();
   if(!MyMenu->event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
     
      al_destroy_display(MyMenu->display);
      al_destroy_timer(MyMenu->timer);
      return 0;
   }
   
   al_init_font_addon();
   al_init_ttf_addon();

   MyMenu->bg = al_load_bitmap("data\\images\\menubg.png");
   CheckBitmap(MyMenu->bg,"data\\images\\menubg.png");
   MyMenu->font = al_load_ttf_font("TELE2.ttf",40,0);

   return MyMenu;

}
/** A Menu felszabaditasa
* @param menu-re mutato pointer
* @return  nincs void
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void FreeMenu(Menu* MyMenu)
{
	al_destroy_display(MyMenu->display);
	al_destroy_timer(MyMenu->timer);
	al_destroy_bitmap(MyMenu->bg);
	al_destroy_font(MyMenu->font);

	free(MyMenu);
}
/** A Menu loopja
* @param menu-re mutato pointer
* @return nincs->void
* @author Pjatacsuk Bence
* @date 2011.10.2
*/
void MenuLoop(Menu* MyMenu)
{

	int redraw;
	bool MenuLoop = true;
//	allapot all;
	/* A megfelelõ event források regisztrálása, display,timer,keyboard */
	
	al_register_event_source(MyMenu->event_queue, al_get_display_event_source(MyMenu->display));
	
	al_register_event_source(MyMenu->event_queue, al_get_timer_event_source(MyMenu->timer));
	
	al_register_event_source(MyMenu->event_queue, al_get_keyboard_event_source());
	
	al_start_timer(MyMenu->timer); // timer inditás
	redraw = true;
	all = newgame;
	while(MenuLoop)
	{
		
		ALLEGRO_EVENT ev; // allegro event struct
		al_wait_for_event(MyMenu->event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) //billentyû lenyomás vizsgálata
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				case ALLEGRO_KEY_W:
					if(all == quit)
					{
						all = newgame;
					}
					

					break;
				case ALLEGRO_KEY_DOWN:
				case ALLEGRO_KEY_S:
					if(all == newgame)
					{
						all = quit;
					}
					break;
				case ALLEGRO_KEY_ENTER:
					if(all == newgame)
					{
						MenuLoop = false;
					}
					else if(all = quit)
					{
						STOP_GAME = 1;
						MenuLoop = false;
					}
					break;

			
			}
	
		}
		else {
			
			redraw = true;
		
		}
		if(redraw && al_is_event_queue_empty(MyMenu->event_queue)) 
		{
			al_draw_bitmap(MyMenu->bg,0,0,0);
			if(all == newgame)
			{
				al_draw_text(MyMenu->font,al_map_rgb(255,128,0),100,200,0,"New Game");
				al_draw_text(MyMenu->font,al_map_rgb(203,203,203),100,300,0,"Quit");
			}
			else
			{
				al_draw_text(MyMenu->font,al_map_rgb(203,203,203),100,200,0,"New Game");
				al_draw_text(MyMenu->font,al_map_rgb(255,128,0),100,300,0,"Quit");
			}
			al_flip_display();
			redraw = false;
		}
		
	}
	
	
}