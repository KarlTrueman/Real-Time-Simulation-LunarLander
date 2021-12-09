// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

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

void DrawLine(BYTE* screen, int screenwidth, int screenheight, int startX, int startY, int endX, int endY)
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
			screen[drawY * screenwidth * 4 + drawX * 4] = 0; //Red
			screen[drawY * screenwidth * 4 + drawX * 4 + 1] = 255; //Green
			screen[drawY * screenwidth * 4 + drawX * 4 + 2] = 0; //Blue
		}

	}
}

void HAPI_Main()
{
	int width{ 1920 };
	int height{ 1080 };

	if (!HAPI.Initialise(width, height))
		return;
	HAPI.SetShowFPS(true);
	BYTE* screen = HAPI.GetScreenPointer();

	//LAnder Position
	float posx = 200;
	float posy = 200;
	//Lander Angle
	float Angle = 0;
	//Lander Velocity
	float Vx = 0;
	float Vy = 0;
	//Lander Thrust
	float ThrustX = 0;
	float ThrustY = 0;

	//Initilise Keyboard Input
	const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();

	while (HAPI.Update())
	{
		//Clear Screen
		memset(screen, 0, (size_t)width * height * 4);
		//Draw Triangle(Lander)
		float TopX = posx;
		float TopY = posy - 20;
		float LeftX = posx - 20;
		float LeftY = posy + 20;
		float RightX = posx + 20;
		float RightY = posy + 20;

		//Controls
		if (KeyData.scanCode['A'])
		{
			Angle -= 0.005;
		}
		else if(KeyData.scanCode['D'])
		{
			Angle += 0.005;
		}
		else if (KeyData.scanCode['W'])
		{
			Vx -= ThrustX /10000;
			Vy -= ThrustY/10000;
		}

		//Rotate Lander
		Rotate(TopX, TopY, posx, posy, Angle);
		Rotate(LeftX, LeftY, posx, posy, Angle);
		Rotate(RightX, RightY, posx, posy, Angle);

		//Thrust
		ThrustY = posy - TopY;
		ThrustX = posx - TopX;

		DrawLine(screen, width, height, LeftX, LeftY, RightX, RightY );
		DrawLine(screen, width, height, LeftX, LeftY, TopX, TopY);
		DrawLine(screen, width, height, RightX, RightY, TopX, TopY);
		//Velocity
		Vy += 0.001;
		posx += Vx;
		posy += Vy;

	}
}

