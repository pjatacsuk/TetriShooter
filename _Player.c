#include "_Player.h"
#include "_Game.h"
#include <math.h>

/** Az ütközés a képernyõ szélével deketálás
* @param key-> a lenyomott gomb iránya, Player-> a játékos struktúra
* @return bool-> igaz, ha ütközés van. hamis ha nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
bool ColDetect(int key,Player* player)
{
	
	
	/* Eset szétválasztás a négy irány szerint */
	switch(key)
	{
		case UP:
			if(((player->coord.y) - player->speed)  > 0) /* a player->speeed a játékos sebességét jelenti,
													   a vizsgálat során ennek változásával együtt nézzük*/
			{
				return 0;
			}
			else
			{
				return 1;
			}
		break;
		
		case DOWN:
			if(((player->coord.y+75) + player->speed)<SCREEN_H)/* a player->speeed a játékos sebességét jelenti,
													         vizsgálat során ennek változásával együtt nézzük*/
			{
				return 0;
			}
			else
			{
				return 1;
			}
		break;

		case LEFT:
			if(((player->coord.x) - player->speed) >= 0) /* a player->speeed a játékos sebességét jelenti,
													   a vizsgálat során ennek változásával együtt nézzük*/
			{
				return 0;
			}
			else
			{
				return 1;
			}

		break;

		case RIGHT:
			if(((player->coord.x+75) + player->speed) <= SCREEN_W) /* a player->speeed a játékos sebességét jelenti,
																a vizsgálat során ennek változásával együtt nézzük*/
			{
				return 0;
			}
			else
			{
				return 1;
			}
		break;
		
		default:
			return 0;
			break;
	}

}

/** Update-eli a player pozicióját
* @param player pointer, a gombok lenyomását tartalmazó tömb
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/

void UpdatePlayer(Player* player,int* keys)
{
	div_t eredm;
	static int db;
	int i;
	Projectile* iter = player->proj_list->eleje->kovetkezo;
	for(i=0;i<4;i++)
	{
		if(ColDetect(i,player) == 0  && keys[i] == 1)
		{
			db++;
			if(db>3 || (keys[SHIFT]==1 && db < 30))
			{
				switch(i)
				{
				case UP:

					player->coord.y -= player->speed;
				
				
					break;
				case DOWN:

					player->coord.y += player->speed;
				
				
					break;
				case LEFT:
				
					player->coord.x -= player->speed;
				
					break;
				case RIGHT:
				
					player->coord.x += player->speed;
				

					break;
				default:
					break;
				}
				if(keys[SHIFT] == 0)
				{
					db = 0;
				}
				else if(db == 30)
				{
					db = 0;
					keys[SHIFT] = 0;
				}
			}
		}
		
				eredm = div((int)(player->coord.x),15);
		player->coord.x = eredm.quot*15;
				eredm = div((int)(player->coord.y),15);
		player->coord.y = eredm.quot*15;
	}
	for(iter;iter != player->proj_list->vege;iter = iter->kovetkezo)
	{
		if(iter->shot != true)
		{
			iter->coord.x = player->coord.x;
			iter->coord.y = player->coord.y-75;
		}
	}

	
					
}

/** Player kirajzolását végzõ program
* @param Game-re mutató pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void DrawPlayer(Game* MyGame)
{
	
	al_draw_bitmap(MyGame->player->bmp[(MyGame->MaxPlayerLife)-(MyGame->player->life_left)],MyGame->player->coord.x,MyGame->player->coord.y,0);
	


}

