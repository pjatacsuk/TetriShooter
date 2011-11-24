#include "_Player.h"
#include "_Game.h"
#include <math.h>

/** Az �tk�z�s a k�perny� sz�l�vel deket�l�s
* @param key-> a lenyomott gomb ir�nya, Player-> a j�t�kos strukt�ra
* @return bool-> igaz, ha �tk�z�s van. hamis ha nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
bool ColDetect(int key,Player* player)
{
	
	
	/* Eset sz�tv�laszt�s a n�gy ir�ny szerint */
	switch(key)
	{
		case UP:
			if(((player->coord.y) - player->speed)  > 0) /* a player->speeed a j�t�kos sebess�g�t jelenti,
													   a vizsg�lat sor�n ennek v�ltoz�s�val egy�tt n�zz�k*/
			{
				return 0;
			}
			else
			{
				return 1;
			}
		break;
		
		case DOWN:
			if(((player->coord.y+75) + player->speed)<SCREEN_H)/* a player->speeed a j�t�kos sebess�g�t jelenti,
													         vizsg�lat sor�n ennek v�ltoz�s�val egy�tt n�zz�k*/
			{
				return 0;
			}
			else
			{
				return 1;
			}
		break;

		case LEFT:
			if(((player->coord.x) - player->speed) >= 0) /* a player->speeed a j�t�kos sebess�g�t jelenti,
													   a vizsg�lat sor�n ennek v�ltoz�s�val egy�tt n�zz�k*/
			{
				return 0;
			}
			else
			{
				return 1;
			}

		break;

		case RIGHT:
			if(((player->coord.x+75) + player->speed) <= SCREEN_W) /* a player->speeed a j�t�kos sebess�g�t jelenti,
																a vizsg�lat sor�n ennek v�ltoz�s�val egy�tt n�zz�k*/
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

/** Update-eli a player pozici�j�t
* @param player pointer, a gombok lenyom�s�t tartalmaz� t�mb
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

/** Player kirajzol�s�t v�gz� program
* @param Game-re mutat� pointer
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.29
*/
void DrawPlayer(Game* MyGame)
{
	
	al_draw_bitmap(MyGame->player->bmp[(MyGame->MaxPlayerLife)-(MyGame->player->life_left)],MyGame->player->coord.x,MyGame->player->coord.y,0);
	


}

