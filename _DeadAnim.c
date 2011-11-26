#include "_DeadAnim.h"
#include "_Game.h"



/** Dead anim reader 
* @param Game-re mutató pointer Dead anim neve, a dead anim indexe
* @return void nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void DeadAnimReader(Game *MyGame,char *dnm,int type)
{
	//egy nagy string összeállítása könnyebb kezelhetõség érdekében
	strcpy(MyGame->DeadAnimPath[type],dnm);
	strcat(MyGame->DeadAnimPath[type],".0.png/");

	strcat(MyGame->DeadAnimPath[type],dnm);
	strcat(MyGame->DeadAnimPath[type],".1.png/");

	strcat(MyGame->DeadAnimPath[type],dnm);
	strcat(MyGame->DeadAnimPath[type],".2.png");

}

/** Dead anim szetvalaszto
* @param Game-re mutató pointer, i index aszerint hogy meik enemy-hez tartozik az animáció
* @return nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
char* DeadAnimCutter(Game *MyGame,int type)
{ 
	//statikus változó segítségével végzem a feldarabolást, strtok féleképpen
	//elégge instabil lehet ha netán tobb mint 3 darabra kene vagni
	static int j = 0;
	char ret[30];
	int k=0;
	while(MyGame->DeadAnimPath[type][j] != '/' && MyGame->DeadAnimPath[type][j] != '\0')
	{
		ret[k] = MyGame->DeadAnimPath[type][j];
		j++;
		k++;
	}
	if(MyGame->DeadAnimPath[type][j] == '\0')
	{
		
		j = 0;
	}
	else if(MyGame->DeadAnimPath[type][j] == '/') 
	{
		j++;
		
	}
	ret[k] = '\0'; 
	
	return ret;
}

/**
* A dead animationok betöltése
* @param Game struktura, int i index a dead anim hez
* @return nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void DeadAnimLoader(Game* MyGame,int i,int type)
{
	int j;
	char path[100];
	for(j=0;j<3;j++)
	{
		strcpy(path,DeadAnimCutter(MyGame,type));
		MyGame->enemy[i]->deadanim->bmp[j] = al_load_bitmap(path);
		CheckBitmap(MyGame->enemy[i]->deadanim->bmp[j],path);
	}
}

/**
* @param Game struktura,int i index a dead anim hez
* @return nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void FreeDeadAnim(Enemy* enemy)
{
	int j;
	for(j=0;j<3;j++)
	{
		
		al_destroy_bitmap(enemy->deadanim->bmp[j]);
	}
}



/** Death animációkat kirajzoló program
* @param Game-re mutató pointer, i index -> az enemy indexe ami meghalt
* @return void->nincs
* @author Pjatacsuk Bence
* @date 2011.10.30
*/
void DrawDeadAnim(Game* MyGame,int i)
{
	
	MyGame->enemy[i]->dead_counter++;
	if(MyGame->enemy[i]->dead_counter<60)
	{
		al_play_sample(MyGame->death_sample,0.3,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);	
	}
	if(MyGame->enemy[i]->dead_counter<20)
	{
		al_draw_bitmap(MyGame->enemy[i]->deadanim->bmp[0],MyGame->enemy[i]->coord.x,MyGame->enemy[i]->coord.y,0); // kis kavarodás az elsõ és második felvan cserélve
	}
	else if((MyGame->enemy[i]->dead_counter>=20) && (MyGame->enemy[i]->dead_counter<=40))
	{
		al_draw_bitmap(MyGame->enemy[i]->deadanim->bmp[1],MyGame->enemy[i]->coord.x,MyGame->enemy[i]->coord.y,0);	
	}
	else if((MyGame->enemy[i]->dead_counter>40) && (MyGame->enemy[i]->dead_counter<60))
	{
		al_draw_bitmap(MyGame->enemy[i]->deadanim->bmp[2],MyGame->enemy[i]->coord.x,MyGame->enemy[i]->coord.y,0);
	}
	else if(MyGame->enemy[i]->dead_counter==60)
	{
		MyGame->enemy[i]->dead_counter = 0;
		MyGame->enemy[i]->ready_to_free = 1;
	}


}