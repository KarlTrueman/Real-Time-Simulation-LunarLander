#include "Simulation.h"
#include "Particles.h"

void Rotate(float& posX, float& posY, float AposX, float AposY, float Angle)
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

void DrawLine(BYTE* screen, int screenwidth, int screenheight, int startX, int startY, int endX, int endY, int Red = 0, int Green = 255, int Blue = 0)
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

void Simulation::Crash()
{
	If_Landed = true;
	Vy = 0;
	Vx = 0;
	Gravity = 0;
	Crashed = true;
	for (int z = 0; z < ParticlesVec.size(); z++)
	{
		ParticlesVec[z]->Setup(posx, posy);
		ParticlesVec[z]->SetIsAlive(true);
	}
}

Simulation::~Simulation()
{
	for (auto& p : ParticlesVec)
		delete p;
}

void Simulation::Run()
{
	//LandingZone
	float LandingX = ((rand() % 1000));

	//Particles
	float TotalParticles = 500;
	for (int x = 0; x <= TotalParticles; x++)
	{
		Particles* newParticle = new Particles();
		ParticlesVec.push_back(newParticle);
	}

	//HAPI Initalisation
	int width{ 1280 };
	int height{ 720 };
	if (!HAPI.Initialise(width, height))
		return;
	HAPI.SetShowFPS(true);
	BYTE* screen = HAPI.GetScreenPointer();
	HAPI_TColour textcol{ HAPI_TColour::RED };
	HAPI_TColour outcol{ HAPI_TColour::RED };
	const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();

	while (HAPI.Update())
	{
		//Delta Time
		Time = clock();
		DeltaTime = Time - OldTime;
		OldTime = Time;

		//Clear Screen
		memset(screen, 0, (size_t)width * height * 4);

		//UI
		HAPI.RenderText(UIX, UIY + (TextSize * 1), textcol, outcol, 0.1, "Velocity Y: " + std::to_string(Vy), 15);
		HAPI.RenderText(UIX, UIY + (TextSize * 2), textcol, outcol, 0.1, "Velocity X: " + std::to_string(Vx), 15);
		HAPI.RenderText(UIX, UIY + (TextSize * 3), textcol, outcol, 0.1, "PosX: " + std::to_string(posx), 15);
		HAPI.RenderText(UIX, UIY + (TextSize * 4), textcol, outcol, 0.1, "PosY: " + std::to_string(posy), 15);
		HAPI.RenderText(UIX, UIY + (TextSize * 5), textcol, outcol, 0.1, "Angle: " + std::to_string(Angle), 15);

		//Draw Triangle(Lander)
		float TopX = posx;
		float TopY = posy - 20;
		float LeftX = posx - 20;
		float LeftY = posy + 20;
		float RightX = posx + 20;
		float RightY = posy + 20;

		//Controls
		if (If_Landed == false)
		{
			if (KeyData.scanCode['A'])
			{
				Angle -= 0.005;
			}
			else if (KeyData.scanCode['D'])
			{
				Angle += 0.005;
			}
			else if (KeyData.scanCode['W'])
			{
				Vx -= ThrustX / 10000;
				Vy -= ThrustY / 10000;
			}
		}
		if (KeyData.scanCode['R'])
		{
			posx = 200;
			posy = 200;
			Vx = 0;
			Vy = 0;
			Gravity = 0.001;
			If_Landed = false;
			Crashed = false;
			Angle = 0;
			LandingX = ((rand() % 1000));
			for (int z = 0; z < ParticlesVec.size(); z++)
			{;
				ParticlesVec[z]->SetIsAlive(false);
			}
		}

		//Rotate Lander
		Rotate(TopX, TopY, posx, posy, Angle);
		Rotate(LeftX, LeftY, posx, posy, Angle);
		Rotate(RightX, RightY, posx, posy, Angle);

		//Thrust
		ThrustY = posy - TopY;
		ThrustX = posx - TopX;

		//Draw Lander
		DrawLine(screen, width, height, LeftX, LeftY, RightX, RightY, 0, 0, 255);
		DrawLine(screen, width, height, LeftX, LeftY, TopX, TopY, 0, 0, 255);
		DrawLine(screen, width, height, RightX, RightY, TopX, TopY, 0, 0, 255);

		// Bottom collision
		if (posy > 700 && posx - 20 > LandingX && posx + 20 < LandingX + 100 && If_Landed == false)
		{
			if (Vy <= 0.4)
			{
				if (Angle > -0.2 && Angle < 0.2)
				{
					If_Landed = true;
					Vy = 0;
					Vx = 0;
					Gravity = 0;
					Crashed = false;
				}
				else
				{
					Crash();
				}
			}
			else
			{
				Crash();
			}
		}
		else if (posy > 700 && If_Landed == false)
		{
			Crash();
		}
		//Left wall colision
		if (posx <= 10)
		{
			Crash();
		}
		//Right wall colison
		else if (posx >= 1270)
		{
			Crash();
		}

		//Update all entitys
		for (Particles* p : ParticlesVec)
			p->Update(screen, width, height);

		//EndGame UI
		if (If_Landed == true && Crashed == true)
		{
			HAPI.RenderText(500, 300, textcol, outcol, 1, "You Crashed!", 64);
		}
		else if (If_Landed == true && Crashed == false)
		{
			HAPI.RenderText(500, 300, textcol, outcol, 1, "You Landed Succesfully!", 64);
		}

		//Velocity
		Vy += Gravity;
		posx += Vx * DeltaTime;
		posy += Vy * DeltaTime;

		//Screen Borders
		//bottom
		DrawLine(screen, width, height, 0, 719, 1280, 719);
		//Left
		DrawLine(screen, width, height, 1, 0, 1, 720);
		//Right
		DrawLine(screen, width, height, 1279, 0, 1279, 720);
		//LandindPAd
		DrawLine(screen, width, height, LandingX, 719, LandingX + 100, 719, 255, 0, 0);
		DrawLine(screen, width, height, LandingX, 718, LandingX + 100, 718, 255, 0, 0);

	}
	
}


