#include "_Projectile.h"
#include "_Game.h" //a függvények itt vannak definiálva <- nem szép megoldás, de mivel a deklarálások sokat függnek a Game tartalmától,
					// ezért igy a legegyszerûbb




/** UJ projectile beszurasa rendezetten
* @param Game-re mutató pointer
* @return void-nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/

void NewListedProjectile(Game *MyGame)
{
	Projectile* iter;
	Projectile* uj;
	int type = 0;
	for(iter = MyGame->player->proj_list->eleje->kovetkezo;
		iter != MyGame->player->proj_list->vege &&
		(iter->shot != true);
		iter = iter->kovetkezo
		)
		{
			// ures;
		}
		// malloc es inicializálás
		uj = (Projectile*)malloc(sizeof(Projectile));
		srand((unsigned)time(0));
		type = (rand()%(MyGame->MaxProjectile));
		uj->bmp = al_load_bitmap(MyGame->ProjectilePath[type]);
		CheckBitmap(uj->bmp,MyGame->ProjectilePath[type]);
		uj->speed = 5.0f;
		uj->type = type;
 		uj->coord.x = MyGame->player->coord.x;
		uj->coord.y = MyGame->player->coord.y-75;
		uj->shot = false;
		//--------------------------------------------------------
		
		//befuzes
		if(iter == MyGame->player->proj_list->vege)
		{
			uj->kovetkezo = iter;
			uj->elozo = iter->elozo;

			iter->elozo->kovetkezo = uj;
			iter->elozo = uj;
		}
		else
		{
 			uj->kovetkezo = iter->kovetkezo;
			uj->elozo = iter;

			iter->kovetkezo->elozo = uj;
			iter->kovetkezo = uj;
		}


}

/** A kovetkezo projectile kilovese
* @param A projectile listara mutato pointer
* @return 1 ha sikerult a kiloves, 0 ha nem
* @author Pjatacsuk Bence
* @date 2011.11.24
*/
bool ShootNextProjectile(ProjectileList* list)
{
	Projectile* iter = list->eleje->kovetkezo;
	for(iter = list->eleje->kovetkezo;iter != list->vege && iter->shot != false;iter = iter->kovetkezo)
	{
		//ures;
	}

	if(iter != list->vege)
	{
		iter->shot = true;
		return 1;
	}
	return 0;
	

}

/** A kovetkezo kilovendo projectile meghatarozasa
* @param A projectile listara mutato pointer
* @return NULL ha nincs kilovendo, a megtalalt elem pointer-e ha van
* @author Pjatacsuk Bence
* @date 2011.11.24
*/
Projectile* NextListedProjectile(ProjectileList* list)
{
	Projectile* iter = list->eleje->kovetkezo;
	for(iter = list->eleje->kovetkezo;iter != list->vege && iter->shot != false;iter = iter->kovetkezo)
	{
		//ures;
	}
	if(iter != list->vege)
	{
		return iter;
	}
	return NULL;

}

/** A projectile-ok y coordinatajanak, illetve felszabaditassanak fuggvenye verzio 2
* @param Game-re mutató pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.11.24
*/
void UpdateListedProjectilePath(Game* MyGame)
{
	Projectile* iter =  MyGame->player->proj_list->eleje->kovetkezo;
	for(iter =  MyGame->player->proj_list->eleje->kovetkezo;
		iter != MyGame->player->proj_list->vege;
		iter = iter->kovetkezo)
	{
		if(iter->shot == 1)
		{
			iter->coord.y -= iter->speed;
		}
		if(iter->coord.y+80 < 0)
		{
			iter = FreeListedProjectile(iter);
			//NewListedProjectile(MyGame);
			
  			
		}
	}
	
	
}

/** A projectile-ok frissítése verzio 2
* @param Game-re mutató pointer
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.11.24
*/
void UpdateListedProjectile(Game *MyGame)
{
	
	
	
	if(MyGame->Keys[SPACE] == 1)
	{
		
		if(ShootNextProjectile(MyGame->player->proj_list) != 1)
		{
			NewListedProjectile(MyGame);							//ha nem volt nem ellot projectile, csinalunk egy ujjat
			ShootNextProjectile(MyGame->player->proj_list);
		}
		NewListedProjectile(MyGame);
		al_play_sample(MyGame->player->sample,0.2,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		
		MyGame->Keys[SPACE] = 0;
	}

	UpdateListedProjectilePath(MyGame);

}


Projectile* FreeListedProjectile(Projectile* projectile)
{
	Projectile* tmp = projectile->elozo;
	projectile->kovetkezo->elozo = projectile->elozo;
	projectile->elozo->kovetkezo = projectile->kovetkezo;
	al_destroy_bitmap(projectile->bmp);
	free(projectile);
	return tmp; 
}

/** A lista felszabaditasa
* @param Listara mutato pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.11.24
*/
void FreeAllListedProjectile(ProjectileList* list)
{
	Projectile* iter = list->eleje->kovetkezo;
	while(iter != list->vege)
	{
		Projectile* tmp = iter->kovetkezo;
		free(iter);
		iter = tmp;
	}
	
	free(list);
}

/** Projectile kirajzolasat vegzo fuggveny  2. verzio
* @param Game-re mutató pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.11.24
*/


void DrawListedProjectile(Game* MyGame)
{
	Projectile* iter = MyGame->player->proj_list->eleje->kovetkezo;
	Projectile* next_draw;
	for(iter = MyGame->player->proj_list->eleje->kovetkezo;
		iter != MyGame->player->proj_list->vege;
		iter = iter->kovetkezo)
	{
		if(iter->shot == 1)
		{
			al_draw_bitmap(iter->bmp,iter->coord.x,iter->coord.y,0);
		
		}

		
	}
	next_draw = NextListedProjectile(MyGame->player->proj_list);
	if(next_draw != NULL)
	{
		al_draw_bitmap(next_draw->bmp,next_draw->coord.x,next_draw->coord.y,0);
	}
}