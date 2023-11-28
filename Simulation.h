#pragma once
#include <windows.h>
#include <iostream>
#include <vector>

void simulation();
float getSimulationTime();
void cameraSimulation(float simulationTime);
void gameObjectSimulation(float simulationTime);
void movePlayer();