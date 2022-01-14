// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include<time.h>
#include<vector>
#include "particles.h";
#include "Simulation.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down


void HAPI_Main()
{
	Simulation Sim;
	Sim.Run();
}

