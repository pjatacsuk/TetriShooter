#include "_Resource.h"
#include <stdio.h>
float FPS = 60;
float SCREEN_W = 600;
float SCREEN_H = 750;
int redraw;

float f_abs(float f)
{
	if(f >= 0)
	{
		return f;
	}
	else
	{
		return f*-1;
	}

}