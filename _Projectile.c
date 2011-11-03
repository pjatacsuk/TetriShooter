#include "_Projectile.h"
#include "_Game.h" //a f�ggv�nyek itt vannak defini�lva <- nem sz�p megold�s, de mivel a deklar�l�sok sokat f�ggnek a Game tartalm�t�l,
					// ez�rt igy a legegyszer�bb




/** A projectile frissitese, uj random projectile lek�r�se
* @param Game-re mutat� pointer, a frissitendo elem indexe
* @return void-nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/

void NewProjectile(Game *MyGame,int i)
{
	int type = 0;
	srand((unsigned)time(0));
	type = (rand()%(MyGame->MaxProjectile));
	MyGame->player->projectile[i]->bmp = al_load_bitmap(MyGame->ProjectilePath[type]);
	MyGame->player->projectile[i]->speed = 5.0f;
	MyGame->player->projectile[i]->type = type;
 	MyGame->player->projectile[i]->coord.x = MyGame->player->coord.x;
	MyGame->player->projectile[i]->coord.y = MyGame->player->coord.y-75;
	MyGame->player->projectile[i]->shot = false;

}


/** A projectile p�ly�j�nak friss�t�se
* @param Game-re mutat� pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void UpdateProjectile(Game *MyGame)
{
	
	int i=0;
	
	if(MyGame->Keys[SPACE] == 1)
	{
		
		MyGame->player->projectile[MyGame->next_projectile_index]->shot = true;
		while(i<4 && MyGame->player->projectile[i]->shot != 0)
		{
			i++;
		}
		if(i<4)
		{
			MyGame->next_projectile_index = i;
			al_play_sample(MyGame->player->sample,0.2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		}
		MyGame->Keys[SPACE] = 0;
	}


	for(i=0;i<4;i++)
	{
		
		if(MyGame->player->projectile[i]->shot == true )
		{
		
			MyGame->player->projectile[i]->coord.y -= MyGame->player->projectile[i]->speed;
		
		}
		
		if(MyGame->player->projectile[i]->coord.y+80 < 0)
		{
			FreeProjectile(MyGame->player->projectile[i]);
			NewProjectile(MyGame,i);
		}
	}

}

/** Projectile mem�ri�j�nak felszabad�t�sa ha kifutott a p�ly�r�l, vagy �tk�z�tt
* @param Projectile-ra mutat� param�ter
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void FreeProjectile(Projectile* projectile)
{
	al_destroy_bitmap(projectile->bmp);
	
	


}


/** Projectile kirajzol�s�t v�gz� program
* @param Game-re mutat� pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.31
*/
void DrawProjectile(Game* MyGame)
{
	int i=0;
	for(i=0;i<4;i++)
	{
		if(MyGame->player->projectile[i]->shot || MyGame->next_projectile_index == i)
		{
			al_draw_bitmap(MyGame->player->projectile[i]->bmp,MyGame->player->projectile[i]->coord.x,MyGame->player->projectile[i]->coord.y,0);
		}
	}
}
