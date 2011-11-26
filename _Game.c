#include "_Game.h"
#include <stdio.h>
#include "_Resource.h"
#include <time.h>
#include <stdlib.h>
#include "_DeadAnim.h"




/** Az allegro keretrendszer inicail�z�sa
* @param Nincs param�ter
* @return Bool-> igaz ha gond van, hamis ha nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
bool _InitAllegro()
{
	if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
   if(!al_init_image_addon())
   {
	fprintf(stderr,"failed to initialize the image adodn\n");
	return -1;
   }
   if(!al_install_audio())
   {
	fprintf(stderr,"failed to init audio");
	return -1;
   }
   if(!al_init_acodec_addon())
   {
	fprintf(stderr,"failed to init acodec");
	   return -1;
   }
   if(!al_reserve_samples(3))
   {
	fprintf(stderr,"failed to reserve 3 samples");
   return -1;
   }
 
   
   return 0;
}

/** A kezdetleges dinamikus mem�ria foglal�sokat kezel� f�ggv�ny
* @param nincs
* @return Game* -> a deklar�lt game pointer
* @author Pjatacsuk Bence
* @date 2011.10.29
*/

Game* _MallocMyGame()
{
	int i,j;
	Projectile* eleje;
	Projectile* vege;
	//A MyGame v�ltoz� dinamikus lefoglal�sa
	Game* MyGame = (Game*)malloc(sizeof(Game));

	//A MyGame-ben l�v� resource t�mb dinamikus lefogal�sa

	for(i=0;i<80;i++)
	{
		MyGame->resource[i] = (Resource*)malloc(sizeof(Resource));
	}

	// player lefoglal�sa

	MyGame->player = (Player*)malloc(sizeof(Player));
	
	// surprise lefoglal�sa
	MyGame->surprise = (Surprise*)malloc(sizeof(Surprise));
	

	//projectile list lefoglal�s
	eleje = (Projectile*)malloc(sizeof(Projectile));
	vege = (Projectile*)malloc(sizeof(Projectile));
	MyGame->player->proj_list = (ProjectileList*)malloc(sizeof(ProjectileList));
	MyGame->player->proj_list->eleje = eleje;
	MyGame->player->proj_list->vege = vege;
	MyGame->player->proj_list->eleje->kovetkezo = vege;
	MyGame->player->proj_list->vege->elozo = eleje;
	
	for(i=0;i<10;i++)
	{
		MyGame->enemy[i] = (Enemy*)malloc(sizeof(Enemy));
		
		for(j=0;j<3;j++)
		{
			MyGame->enemy[i]->deadanim = (DeadAnim*)malloc(sizeof(DeadAnim));
		}
	}
	MyGame->SurprisePath = (char**)malloc(5*sizeof(char*));
	for(i=0;i<MAX_PATH_COUNT;i++)
	{
		MyGame->EnemyPath[i] = (char*)malloc(50*sizeof(char));
		MyGame->DeadAnimPath[i] = (char*)malloc(100*sizeof(char));
		MyGame->ProjectilePath[i] = (char*)malloc(50*sizeof(char));
		MyGame->SurprisePath[i] = (char*)malloc(50*sizeof(char));
	}
	MyGame->BgPath = (char***)malloc(10*sizeof(char**));
	for(i=0;i<10;i++)
	{
		MyGame->BgPath[i] = (char**)malloc(10*sizeof(char*));
		for(j=0;j<11;j++)
		{
			MyGame->BgPath[i][j] = (char*)malloc(50*sizeof(char));
		} 
	}
	
	
	return MyGame;
}

/** A memoria felszabaditasa
* @param Game pointer
* @return nincs->void
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void _FreeMyGame(Game* MyGame)
{
	int i = 0,j=0;
	al_destroy_timer(MyGame->timer);
	al_destroy_display(MyGame->display);
	
	
	
	
	for(i=0;i<80;i++)
	{
		
		free(MyGame->resource[i]);
	}
	
	FreeAllListedProjectile(MyGame->player->proj_list);


	for(i=0;i<10;i++)
	{
		FreeEnemy(MyGame->enemy[i]);
		free(MyGame->enemy[i]);
		for(j=0;j<11;j++)
		{
			free(MyGame->BgPath[i][j]);
			
		}
		
	}
	free(MyGame->BgPath);
	for(i=0;i<5;i++)
	{
		free(MyGame->EnemyPath[i]);
		free(MyGame->DeadAnimPath[i]);
		free(MyGame->ProjectilePath[i]);
		free(MyGame->SurprisePath[i]);
	}
	free(MyGame->surprise);
	for(i=0;i<5;i++)
	{
		al_destroy_bitmap(MyGame->player->bmp[i]);
	}

	al_destroy_sample(MyGame->player->sample);
	al_destroy_sample(MyGame->player->boost);
	al_destroy_sample(MyGame->death_sample);
	
	free(MyGame->player);

	/*if(MyGame->surprise->bmp)
	{
	al_destroy_bitmap(MyGame->surprise->bmp); probl�m�s
	free(MyGame->surprise);
	} */

	free(MyGame);

}
/** A j�t�k resourceainak initaliz�l�sa 
* @param a resource file �tvonala
* @return Bool-> igaz ha gond van, hamis ha minden rendben
* @author Pjatacsuk Bence
* @date 2011.10.29
*
*/
 Game* _InitGame(char* file_path)
{
	int i=0;
	// Game-hez mem�ria allok�l�sa
	Game* MyGame = _MallocMyGame();
	
	// Timer kre�l�sa
	MyGame->timer = al_create_timer(1.0 / FPS);

	   if(!MyGame->timer) 
	   {
		  fprintf(stderr, "failed to create timer!\n");
		  return 0;
	   }

	   //display kre�l�sa
   
	   MyGame->display = al_create_display(SCREEN_W,SCREEN_H);
	   if(!MyGame->display) 
	   {
		  fprintf(stderr, "failed to create display!\n");
		  al_destroy_timer(MyGame->timer);
		  return 0;
	   } 

	   //event queue kre�l�sa

	  MyGame->event_queue = al_create_event_queue();
   if(!MyGame->event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
     
      al_destroy_display(MyGame->display);
      al_destroy_timer(MyGame->timer);
      return 0;
   }
   MyGame->MaxBackGround = 0;
	MyGame->MaxEnemy = 0;    
	MyGame->MaxProjectile = 0;

	//surprise bmp null�z�s
	MyGame->surprise->bmp = NULL;
	MyGame->surprise->sample = NULL;

	//Gamer resource ok beolvas�sa a fileb�l
	_GameResourceReader(MyGame,file_path);

	//player inicail�z�sa
	MyGame->player->coord.x = 300;
	MyGame->player->coord.y = 500;
	MyGame->player->speed = 15;
	MyGame->player->life_left = 4;
	MyGame->player->boost = al_load_sample("data\\sounds\\boost.wav");
	//surprise incializ�l�s
	
	//projectile inicializ�l�s
	
	NewListedProjectile(MyGame);

	//enemy-ik inicializ�l�sa
	for(i=0;i<10;i++)
	{
		NewEnemy(MyGame,i);
	}
	
	//A billenty� lenyom�s inicializ�l�sa

	MyGame->Keys[0] = 0;
	MyGame->Keys[1] = 0;
	MyGame->Keys[2] = 0;
	MyGame->Keys[3] = 0;
	MyGame->Keys[4] = 0;
	MyGame->Keys[5] = 0;

	// next projectile index inicializ�l�s
	MyGame->next_projectile_index = 0;

	//next background index incializ�l�s
	MyGame->next_bgbackground_index = 1;
	MyGame->next_bgforeground_index = 0;

	
	//enemy down null�z�s
	MyGame->enemy_down = 0;

	//bitmap pointerek null�z�sa
	MyGame->bg_background = NULL;
	MyGame->bg_foreground = NULL;
	
	
	

	//h�tt�r felt�lt�se
	GameBGLoad(MyGame,MyGame->enemy_down);


	
	return MyGame;
}



/** A kirajzol�st v�gz� program
* @param Game pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*
*/ 
void Draw(Game *MyGame)
{
	
	al_draw_bitmap(MyGame->bg_background,0,0,0);
	al_draw_bitmap(MyGame->bg_foreground,0,0,0);
	DrawPlayer(MyGame);
	DrawListedProjectile(MyGame);
	DrawSurprise(MyGame->surprise);
	DrawEnemy(MyGame);
	
}


/**A j�t�k loop r�sze, itt t�rt�nik az input output kezel�s, a program f� r�sze
* @param Game pointer
* @return bool -> ha baj van true, ha nincs false
* @author Pjatacsuk Bence
- @date 2011.10.29
*
*/
bool _GameLoop(Game *MyGame)
{
	bool GameRunning = true;

	/* A megfelel� event forr�sok regisztr�l�sa, display,timer,keyboard */
	
	al_register_event_source(MyGame->event_queue, al_get_display_event_source(MyGame->display));
	
	al_register_event_source(MyGame->event_queue, al_get_timer_event_source(MyGame->timer));
	
	al_register_event_source(MyGame->event_queue, al_get_keyboard_event_source());
	
	al_start_timer(MyGame->timer); // timer indit�s
	redraw = true;
	while(GameRunning)
	{
		ALLEGRO_EVENT ev; // allegro event struct
		al_wait_for_event(MyGame->event_queue, &ev);
			
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) //billenty� lenyom�s vizsg�lata
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					MyGame->Keys[UP] = 1;
					
				break;
				
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					MyGame->Keys[LEFT] = 1;
					
				break;

				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					MyGame->Keys[DOWN] = 1;
					
				break;

				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					MyGame->Keys[RIGHT] = 1;
					
				break;

				case ALLEGRO_KEY_SPACE:
					MyGame->Keys[SPACE] = 1;
					
					break;
				case ALLEGRO_KEY_LSHIFT:
				case ALLEGRO_KEY_RSHIFT:
					MyGame->Keys[SHIFT] = 1;
					al_play_sample(MyGame->player->boost,0.3,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
					break;
				
				default:
					break;
			}
				redraw = true; // ujrarajzol�s
		
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) // billenty� felenged�s vizsg�lata
		{
			switch(ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_W:
					case ALLEGRO_KEY_UP:
						MyGame->Keys[UP] = 0;
					break;
				
					case ALLEGRO_KEY_A:
					case ALLEGRO_KEY_LEFT:
						MyGame->Keys[LEFT] = 0;
					break;

					case ALLEGRO_KEY_S:
					case ALLEGRO_KEY_DOWN:
						MyGame->Keys[DOWN] = 0;
						
					break;

					case ALLEGRO_KEY_D:
					case ALLEGRO_KEY_RIGHT:
						MyGame->Keys[RIGHT] = 0;
						break;

					case ALLEGRO_KEY_SPACE:
					
					MyGame->Keys[SPACE] = 0;
					break;
					case ALLEGRO_KEY_LSHIFT:
						MyGame->Keys[SHIFT] = 0;
					break;

					default:
						break;
				}
					redraw = true; // ujrarajzol�s
		
		
		
		}
		else {redraw = true;}
	
		if(redraw && al_is_event_queue_empty(MyGame->event_queue)) 
		{
			 // kirajzol�s �s friss�t�sek
			 redraw = false;
			 
			 Draw(MyGame);
			 UpdatePlayer(MyGame->player,MyGame->Keys);
			 UpdateListedProjectile(MyGame);
			 __UpdateEnemy(MyGame);
			 UpdateSurprise(MyGame->surprise);
		 
			 al_flip_display();
	
		}
		if(MyGame->player->life_left<0)
		{
			GameRunning = false;
			_FreeMyGame(MyGame);
			// felszabad�t�s
		}


	}
}



/**
*A jatekhoz szukseges resource (mp3,png,txt) fileok
*beolvasasa egy resource nevezet� strukturaba.
*Ezzel automatizalva van a resource-k definialasa
* @param a Game nev� struktura, a .txt file utvonala, a resource-okat tartalmaz� tomb
* @return -nincs f
* @author Pjatacsuk Bence
* @date 2011.10.29
*
*/
void _GameResourceReader(Game *MyGame,char *file_path)
{
	FILE *fp;
	
	char path[256];
	char* c;
	int p;
	int p2;
	
	int count=0;
	int j=0,i=0,k = 0;

	fp=fopen(file_path,"rt");
	
	if(fp == NULL)
	{
		fprintf(stderr,"Nem siker�lt a file megnyit�sa");
	}
	
	while(fscanf(fp,"%s",path)!=EOF)
	{
		
	
			
			strcpy(MyGame->resource[i]->name,strtok(path,".")); // A file kiterjeszt�s lev�laszt�sa igy indexelhet� lesz n�v alapj�n
			
			if(strcmp(MyGame->resource[i]->name,"bg") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */
				
				c = strtok(NULL,".");							// . pontig m�g egy szabdal�s. eredm�ny ->index
				
				p = atoi(c);									//index integer alakit�sa
				strcat(MyGame->resource[i]->name,".");			//name-hez pont hozz� rak�sa hogy j� legyen az utvonal
				
				strcat(MyGame->resource[i]->name,c);			//c index visszaf�z�se

				c = strtok(NULL,".");							//k�vetkez� index megkeres�se
				p2 = atoi(c);								
				strcat(MyGame->resource[i]->name,".");			//marad�k index visszaf�z�se
				strcat(MyGame->resource[i]->name,c);
				strcat(MyGame->resource[i]->name,".png");
				strcpy(MyGame->BgPath[p][p2],MyGame->resource[i]->name); //t�rool�s

				MyGame->MaxBackGround = p+1;			// maximum background sz�m�nak kisz�m�t�sa
			}
			else if(strcmp(MyGame->resource[i]->name,"player") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */
				c = strtok(NULL,".");
				
				p = atoi(c);
				strcat(MyGame->resource[i]->name,".");
				strcat(c,".png");
				strcat(MyGame->resource[i]->name,c);
				MyGame->player->bmp[p] = al_load_bitmap(MyGame->resource[i]->name);
				CheckBitmap(MyGame->player->bmp[p],MyGame->resource[i]->name);
			
				MyGame->MaxPlayerLife = p;//Max Player �let anim�ci� sz�m�nak kisz�m�t�sa (val�j�ban az �let sz�ma: p+1);
			}
			else if(strcmp(MyGame->resource[i]->name,"projectile") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */

				c = strtok(NULL,".");
				
				p = atoi(c);
				strcat(MyGame->resource[i]->name,".");
				strcat(c,".png");
				strcat(MyGame->resource[i]->name,c);
				strcpy(MyGame->ProjectilePath[p],MyGame->resource[i]->name);

				MyGame->MaxProjectile = p+1; // max projectile sz�m�nak kisz�m�t�sa
			
			}
			
			else if(strcmp(MyGame->resource[i]->name,"enemy") ==0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */

				c = strtok(NULL,".");
				
				p = atoi(c);
				strcat(MyGame->resource[i]->name,".");
				strcat(c,".png");
				strcat(MyGame->resource[i]->name,c);
				strcpy(MyGame->EnemyPath[p],MyGame->resource[i]->name);

				MyGame->MaxEnemy = p+1; // max enemy sz�m�nak kisz�m�t�sa
			}
			else if(strcmp(MyGame->resource[i]->name,"enemydead") ==0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */

				c = strtok(NULL,".");
				
				p = atoi(c);
				strcat(MyGame->resource[i]->name,".");
				
				strcat(MyGame->resource[i]->name,c);
				
				DeadAnimReader(MyGame,MyGame->resource[i]->name,p);

				
				
			}
			else if(strcmp(MyGame->resource[i]->name,"surprise") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\images\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */

				c = strtok(NULL,".");
				
				p = atoi(c);

				strcat(MyGame->resource[i]->name,".");			//name-hez pont hozz� rak�sa hogy j� legyen az utvonal
				
				strcat(MyGame->resource[i]->name,c);			//c index visszaf�z�se

				c = strtok(NULL,".");							//k�vetkez� index megkeres�se
				p2 = atoi(c);								
				strcat(MyGame->resource[i]->name,".");			//marad�k index visszaf�z�se
				strcat(MyGame->resource[i]->name,c);
				strcat(MyGame->resource[i]->name,".png");
				
				MyGame->surprise->dir = p2; // az ir�ny amerre megy a surprise

				strcpy(MyGame->SurprisePath[p],MyGame->resource[i]->name);	
			
			}
			else if(strcmp(MyGame->resource[i]->name,"shoot") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\sounds\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */
					
			
				strcat(MyGame->resource[i]->name,".wav");								//hanganyang bet�lt�se
				MyGame->player->sample = al_load_sample(MyGame->resource[i]->name);
			
			
			}
			else if(strcmp(MyGame->resource[i]->name,"death") == 0)
			{
				/* az ut alakitasa, tisztabb file struktura erdekeben */
				char tmp[100];
				strcpy(tmp,"data\\sounds\\");
				strcat(tmp,MyGame->resource[i]->name);
				strcpy(MyGame->resource[i]->name,tmp);
				/* ***************************************************** */

				strcat(MyGame->resource[i]->name,".wav");								//hanganyang bet�lt�se
				MyGame->death_sample = al_load_sample(MyGame->resource[i]->name);
			}
			
			
			
		
			i++; // index n�vel�se fontos
		
		
		}
		
		/*
		for(i=0;i<11;i++)
		{
			printf("%s\n",MyGame->BgPath[0][i]);
			
			printf("%s\n",MyGame->BgPath[1][i]);
		} 
		
	*/
	MyGame->GameResDB = i; // a resource darabok sz�ma

	fclose(fp);
}







/** A hatter betoltese
* @param Game-re mutat� pointer, a hatter indexe
* @return void -> nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/
void GameBGLoad(Game* MyGame,int i)
{
	if(MyGame->bg_foreground)
	{
		al_destroy_bitmap(MyGame->bg_foreground);
	}
	if(MyGame->bg_background)
	{
		al_destroy_bitmap(MyGame->bg_background);
	}
	
	MyGame->bg_foreground = al_load_bitmap(MyGame->BgPath[MyGame->next_bgforeground_index][i]);
	CheckBitmap(MyGame->bg_foreground,MyGame->BgPath[MyGame->next_bgforeground_index][i]);

	MyGame->bg_background = al_load_bitmap(MyGame->BgPath[MyGame->next_bgbackground_index][0]);
	CheckBitmap(MyGame->bg_background,MyGame->BgPath[MyGame->next_bgbackground_index][0]);
}


