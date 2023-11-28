#include "Data.h"
#include "Simulation.h"
#include <time.h>


float last_time=0.0;
float getSimulationTime() {
	clock_t current_time = clock();
	float simulationTime = float(current_time - last_time) / CLOCKS_PER_SEC;
	last_time = current_time;
	return simulationTime;
}

void cameraSimulation(float simulationTime) {
	if (GetAsyncKeyState(VK_LBUTTON)){
		int CenterW = glutGet(GLUT_WINDOW_WIDTH) / 2;
		int CenertH = glutGet(GLUT_WINDOW_HEIGHT) / 2;

		float mAngleX = CenterW - MouseXY.x;
		float mAngleY = CenertH - MouseXY.y;
		float speedMouse = simulationTime/5;

		if (GetCursorPos(&MouseXY)) {
			cam1.rotateLeftRight(mAngleX * speedMouse);
			cam1.rotateUpDown(mAngleY * speedMouse);
			SetCursorPos(MouseXY.x, MouseXY.y);
		}
	}

	float speedKey = simulationTime*20;
	cout << speedKey*20 << endl;

	if (GetAsyncKeyState(VK_LEFT))		cam1.rotateLeftRight(speedKey);
	if (GetAsyncKeyState(VK_RIGHT))		cam1.rotateLeftRight(-speedKey);
	if (GetAsyncKeyState(VK_ADD))		cam1.zoomInOut(-speedKey);
	if (GetAsyncKeyState(VK_SUBTRACT))	cam1.zoomInOut(speedKey);
	if (GetAsyncKeyState(VK_UP))		cam1.rotateUpDown(-speedKey);
	if (GetAsyncKeyState(VK_DOWN))		cam1.rotateUpDown(speedKey);
}

//simualtion all objects
void gameObjectSimulation(float simulationTime) {
	if (player!=nullptr) {
		player->simulate(simulationTime);
	}
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr)
				mapObjects[i][j]->simulate(simulationTime);
		}
	}
}

void movePlayer() {
	float speed = 5.0f;
	ivec2 curPosPlayer = player->getPosition();
	if ((GetAsyncKeyState(87)) && (!player->isMoving())) {	//	W
		if (passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 0) {
			player->move(MoveDirection::UP,speed);
		}
	}

	if ((GetAsyncKeyState(83)) && (!player->isMoving())) {	//	S
		if (passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 0) {
			player->move(MoveDirection::DOWN,speed);
		}
	}

	if ((GetAsyncKeyState(65)) && (!player->isMoving())) {	//	A
		if (passabilityMap[curPosPlayer.x-1][curPosPlayer.y] == 0) {
			player->move(MoveDirection::LEFT,speed);
		}
	}

	if ((GetAsyncKeyState(68)) && (!player->isMoving())) {	//	D
		if (passabilityMap[curPosPlayer.x+1][curPosPlayer.y] == 0) {
			player->move(MoveDirection::RIGHT,speed);
		}
	}
}


void simulation() {
	float simualtionTime = getSimulationTime();
	cameraSimulation(simualtionTime);
	gameObjectSimulation(simualtionTime);
	movePlayer();
	glutPostRedisplay();
};