#include "Particles.h"
#include "Simulation.h"
#include <math.h>

Particles::Particles()
{
	Vx = float (rand() % 10);
	Vy = float (rand() % 10);

	Direction = float(rand() % 25);
	 Speed = float(rand() % 25);

	 PosX = 640;
	 PosY = 360;

	  Red = rand() % 255;
	  Green = rand() % 255;
	  Blue = rand() % 255;

}

void Particles::Setup(float LanderX, float LanderY)
{
	PosX = LanderX;
	PosY = LanderY;
}

void Particles::Update(BYTE* screen, int screenwidth, int screenheight)
{
	if (IsAlive == true)
	{
		if (LifeSpan > 0)
		{
			PosX += float (Speed * cos(Direction));
			PosY += float (Speed * sin(Direction));


			if (PosX > 0 && PosX < screenwidth && PosY > 0 && PosY < screenheight)
			{
				screen[PosY * screenwidth * 4 + PosX * 4] = Red; //Red
				screen[PosY * screenwidth * 4 + PosX * 4 + 1] = Green; //Green
				screen[PosY * screenwidth * 4 + PosX * 4 + 2] = Blue; //Blue
				//LifeSpan -= 1;
			}
		}
	}
	if (IsAlive == false)
	{
		PosX = 640;
		PosY = 360;
	}
	
}
