#include "_Enemy.h"
#include "_Game.h" //a f�ggv�nyek itt vannak defini�lva <- nem sz�p megold�s, de mivel a deklar�l�sok sokat f�ggnek a Game tartalm�t�l,
					// ez�rt igy a legegyszer�bb







/** Az uj enemy felvetele az i index helyre
* @param Game pointere, i -> enemy tomb indexe, ahova frissiteni akarunk, type -> az enemy tipusa
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void NewEnemy(Game* MyGame,int i)
{
	static float tier = 0;
	static int count = 0;
	int rnd;
	int type;
	
	
	tier -= 200;
	count++;
	srand((unsigned)time(0));
	rnd = rand()%8;

	MyGame->enemy[i]->coord.x = rnd * 75;
	MyGame->enemy[i]->coord.y = tier; //statikus v�ltoz�val k�nnyen tudok egyenletesen eloszl� ellenfeleket be�ll�tani
	type = rand()%MyGame->MaxEnemy;
	MyGame->enemy[i]->type = type;
	
	//dead animationok inicializ�l�sa
	MyGame->enemy[i]->bmp = al_load_bitmap(MyGame->EnemyPath[type]);
	MyGame->enemy[i]->ready_to_free = 0;
	MyGame->enemy[i]->dead_counter = 0;

	MyGame->enemy[i]->speed = 15;
	MyGame->enemy[i]->dead = 0;
	
	
	DeadAnimLoader(MyGame,i,type);

	if(count>=10)
	{
		count = 0;
		tier = 0;

	}
}


/** Az enemy bitmapjanak torlese
* @param Enemy-re mutat� pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void FreeEnemy(Enemy *enemy)
{
	al_destroy_bitmap(enemy->bmp);
	FreeDeadAnim(enemy);

}


/** Az enemy-k frissitese, es az enemykkel kapcsolatos dolgok kezelese
* @param Game -re mutato pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/

void UpdateEnemy(Game *MyGame)
{
	int j,i=0;
	static int db = 0;
	db++;
	for(i=0;i<10;i++)
	{
		if(db>20)
		{
			MyGame->enemy[i]->coord.y += MyGame->enemy[i]->speed; // statikus v�ltoz� seg�ts�g�vel szab�lyozzuk a block sebess�gt
		
		}
		if(MyGame->enemy[i]->coord.y > SCREEN_H) 
		{
			FreeEnemy(MyGame->enemy[i]);
			NewEnemy(MyGame,i);				//ha egy ellens�g el�ri a k�perny� alj�t veszt�nk egy �letet
			MyGame->player->life_left--;	//�s �j ellenf�l ker�l a list�ra
		}
		for(j=0;j<4;j++)
		{
			if(MyGame->player->projectile[j]->shot == 1)
			{
				if(f_abs(MyGame->player->projectile[j]->coord.x - MyGame->enemy[i]->coord.x) < 70 &&		//az �tk�z�s vizsg�l�sa
					(f_abs((MyGame->player->projectile[j]->coord.y) - MyGame->enemy[i]->coord.y)) < 0.1f && 
					MyGame->enemy[i]->dead != 1)
				{
					if(
						 (f_abs(MyGame->player->projectile[j]->coord.x - MyGame->enemy[i]->coord.x)) < 0.1f &&	//a tal�lat vizsg�l�sa
						 (f_abs((MyGame->player->projectile[j]->coord.y) - MyGame->enemy[i]->coord.y)) < 0.1f &&
						 (MyGame->enemy[i]->type == MyGame->player->projectile[j]->type)
					 )
					{
						
  							MyGame->enemy_down++;
							if(MyGame->enemy_down == 11) // a h�tt�r lebom�l�s�nak m�velete
							{
								MyGame->enemy_down = 0;
								
								
								MyGame->next_bgforeground_index++;
								if(MyGame->next_bgforeground_index == MyGame->MaxBackGround)
								{
									MyGame->next_bgforeground_index = MyGame->next_bgbackground_index; // ha v�ge van a h�tterek sz�m�nak ciklikusan visszat�r
								}																		// az elej�re
								MyGame->next_bgbackground_index++;
								if(MyGame->next_bgbackground_index == MyGame->MaxBackGround)
								{
									MyGame->next_bgbackground_index = 0;
								}
								
								
							
							}
							if(MyGame->enemy_down == 5 && MyGame->next_bgforeground_index >= 1)
							{
								NewSurprise(MyGame->surprise,MyGame->SurprisePath[MyGame->next_bgforeground_index - 1]);
							}

							
							MyGame->enemy[i]->dead = 1; //tal�lat eset�n meghal az enemy
							GameBGLoad(MyGame,MyGame->enemy_down);
							
							
							
						
					
						
					}

					FreeProjectile(MyGame->player->projectile[j]); //�tk�z�s eset�n a projectile elv�sz
					NewProjectile(MyGame,j);
				}

			}
		}

		if(MyGame->enemy[i]->ready_to_free == 1)
		{
			FreeEnemy(MyGame->enemy[i]); //dead animation v�g�n felszabad�tjuk a resource-t
			NewEnemy(MyGame,i); 
		}
	
	}
	if(db>20)
	{
		db = 0;
	}



}

/** Az enemy-k kirajzol�s��rt felel�s 
* @param Game-re mutat� pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/

void DrawEnemy(Game *MyGame)
{
	int i=0;
	for(i=0;i<10;i++)
	{
		if(MyGame->enemy[i]->dead != 1)
		{
			al_draw_bitmap(MyGame->enemy[i]->bmp,MyGame->enemy[i]->coord.x,MyGame->enemy[i]->coord.y,0);
		}
		else
		{
			DrawDeadAnim(MyGame,i);
		}
	}
	
}
