#pragma once
#include <HAPI_lib.h>
#include "Simulation.h"
using namespace HAPISPACE;
//class Simulation;
class Particles
{
public:
	Simulation Sim;
	Particles();
	void Setup(float LanderX, float LanderY);
	void SetIsAlive(bool Alive) { IsAlive = Alive; }
	void Update(BYTE* screen,  int screenwidth, int screenheight);
private:
	bool IsAlive = false;
	int PosX = 640;
	int PosY = 360;
	float Vx = 0;
	float Vy = 0;
	float Speed = 0;
	float Direction = 0;
	float LifeSpan = 9;
	int Red = rand() % 255;
	int Green = rand() % 255;
	int Blue = rand() % 255;
};

