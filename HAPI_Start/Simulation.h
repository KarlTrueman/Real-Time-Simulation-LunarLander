#pragma once
#include <HAPI_lib.h>
#include<vector>

using namespace HAPISPACE;
class Particles;
class Simulation
{
public:
	~Simulation();
	void Run();
	float GetDeltaTime() { return DeltaTime; }
	float GetPosX() { return posx; }
	float GetPosY() { return posy; }
	
private:
	std::vector<Particles*> ParticlesVec;
	// DeltaTime
	float Time = 0;
	float OldTime = 0;
	float DeltaTime = 0;
	void Crash();

	bool Crashed = false;
	bool If_Landed = false;
	float Gravity = 0.001;
	//Lander Position
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
	//text
	int TextSize = 15;
	int UIX = 10;
	int UIY = 0;
	

};

