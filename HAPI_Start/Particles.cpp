#include "Particles.h"
#include "Simulation.h"
#include <math.h>

Particles::Particles()
{
	Vx = float (2 * 3.14 * (rand() / RAND_MAX));
	Vy = float (rand()/ RAND_MAX);

	Direction = (2 * 3.14 * (rand()));
	 Speed = float (rand()%10);

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

void Particles::DrawLine(BYTE* screen, int screenwidth, int screenheight, int startX, int startY, int endX, int endY, int Red, int Green, int Blue)
{
	int lengthX = endX - startX;
	int lengthY = endY - startY;
	int length = sqrt((lengthX * lengthX) + (lengthY * lengthY));
	float calcX = startX;
	float calcY = startY;

	for (float i = 0; i < 1; i += 1.0f / length / 2)
	{
		calcX = (1 - i) * startX + i * endX;
		calcY = (1 - i) * startY + i * endY;

		int drawX = calcX;
		int drawY = calcY;
		if (drawX > 0 && drawX < screenwidth && drawY > 0 && drawY < screenheight)
		{
			screen[drawY * screenwidth * 4 + drawX * 4] = Red; //Red
			screen[drawY * screenwidth * 4 + drawX * 4 + 1] = Green; //Green
			screen[drawY * screenwidth * 4 + drawX * 4 + 2] = Blue; //Blue
		}

	}
}

void Particles::Rotate(float& posX, float& posY, float AposX, float AposY, float Angle)
{
	float TPosX;
	float TPosY;
	float RPosX;
	float RPosY;
	float FPosX;
	float FPosY;

	float sinAngle;
	float cosAngle;

	sinAngle = sin(Angle);
	cosAngle = cos(Angle);

	TPosX = posX - AposX;
	TPosY = posY - AposY;

	RPosX = (TPosX * cosAngle) - (TPosY * sinAngle);
	RPosY = (TPosX * sinAngle) + (TPosY * cosAngle);

	FPosX = RPosX + AposX;
	FPosY = RPosY + AposY;

	posX = FPosX;
	posY = FPosY;
}


void Particles::Update(BYTE* screen, int screenwidth, int screenheight)
{
	//if (IsAlive == true)
	//{
	//	if (LifeSpan > 0)
	//	{
	//		PosX += float (Speed * cos(Direction));
	//		PosY += float (Speed * sin(Direction));


	//		if (PosX > 0 && PosX < screenwidth && PosY > 0 && PosY < screenheight)
	//		{
	//			screen[PosY * screenwidth * 4 + PosX * 4] = Red; //Red
	//			screen[PosY * screenwidth * 4 + PosX * 4 + 1] = Green; //Green
	//			screen[PosY * screenwidth * 4 + PosX * 4 + 2] = Blue; //Blue
	//			LifeSpan -= 1;
	//		}
	//	}
	//}
	//if (IsAlive == false)
	//{
	//	PosX = 640;
	//	PosY = 360;
	//}

	if (IsAlive == true)
	{
		if (LifeSpan > 0)
		{
			PosX += float (Speed * cos(Direction) /2 );
			PosY += float (Speed * sin(Direction) /2);


			if (PosX > 0 && PosX < screenwidth && PosY > 0 && PosY < screenheight)
			{
				DrawLine(screen, screenwidth, screenheight, PosX, PosY, PosX + 10, PosY + 10, Red, Green, Blue);
				LifeSpan -= 1;
			}
		}
	}
	if (IsAlive == false)
	{
		PosX = 640;
		PosY = 360;
	}

	
}


