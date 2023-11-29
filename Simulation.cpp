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
	float speedKey = simulationTime * 20;

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
	float speed = 4.0f;
	ivec2 curPosPlayer = player->getPosition();
	//W
	if ((GetAsyncKeyState(87)) && (!player->isMoving())) {
		if (passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 0) {
			player->move(MoveDirection::UP,speed);
		}
		else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] == 0)) {
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] = 0;
				passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] = 1;
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1]->move(MoveDirection::UP, speed/2);
				mapObjects[curPosPlayer.x][curPosPlayer.y - 2] = mapObjects[curPosPlayer.x][curPosPlayer.y - 1];
				mapObjects[curPosPlayer.x][curPosPlayer.y - 1] = nullptr;
				player->move(MoveDirection::UP, speed/2);
		}
		else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y - 3] == 0)) {
			passabilityMap[curPosPlayer.x][curPosPlayer.y - 1] = 0;
			passabilityMap[curPosPlayer.x][curPosPlayer.y - 2] = 1;
			passabilityMap[curPosPlayer.x][curPosPlayer.y - 3] = 1;
			mapObjects[curPosPlayer.x][curPosPlayer.y - 2]->move(MoveDirection::UP, speed / 4);
			mapObjects[curPosPlayer.x][curPosPlayer.y - 1]->move(MoveDirection::UP, speed / 4);
			mapObjects[curPosPlayer.x][curPosPlayer.y - 3] = mapObjects[curPosPlayer.x][curPosPlayer.y - 2];
			mapObjects[curPosPlayer.x][curPosPlayer.y - 2] = mapObjects[curPosPlayer.x][curPosPlayer.y - 1];
			mapObjects[curPosPlayer.x][curPosPlayer.y - 1] = nullptr;
			player->move(MoveDirection::UP, speed / 4);
		}
	}
	//S
	if ((GetAsyncKeyState(83)) && (!player->isMoving())) {
		if (passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 0) {
			player->move(MoveDirection::DOWN,speed);
		}
		else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] == 0)) {
			passabilityMap[curPosPlayer.x][curPosPlayer.y + 1] = 0;
			passabilityMap[curPosPlayer.x][curPosPlayer.y + 2] = 1;
			mapObjects[curPosPlayer.x][curPosPlayer.y + 1]->move(MoveDirection::DOWN, speed / 2);
			mapObjects[curPosPlayer.x][curPosPlayer.y + 2] = mapObjects[curPosPlayer.x][curPosPlayer.y + 1];
			mapObjects[curPosPlayer.x][curPosPlayer.y + 1] = nullptr;
			player->move(MoveDirection::DOWN, speed / 2);
		}
		//Двигаем 2 кубика
		else if ((passabilityMap[curPosPlayer.x][curPosPlayer.y+1] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y+2] == 1) and
			(passabilityMap[curPosPlayer.x][curPosPlayer.y+3] == 0)) {
			passabilityMap[curPosPlayer.x][curPosPlayer.y+1] = 0;
			passabilityMap[curPosPlayer.x][curPosPlayer.y+2] = 1;
			passabilityMap[curPosPlayer.x][curPosPlayer.y+3] = 1;
			mapObjects[curPosPlayer.x][curPosPlayer.y+2]->move(MoveDirection::DOWN, speed / 4);
			mapObjects[curPosPlayer.x][curPosPlayer.y+1]->move(MoveDirection::DOWN, speed / 4);
			mapObjects[curPosPlayer.x][curPosPlayer.y+3] = mapObjects[curPosPlayer.x][curPosPlayer.y+2];
			mapObjects[curPosPlayer.x][curPosPlayer.y+2] = mapObjects[curPosPlayer.x][curPosPlayer.y+1];
			mapObjects[curPosPlayer.x][curPosPlayer.y+1] = nullptr;
			player->move(MoveDirection::DOWN, speed / 4);
		}
	}
	//A
	if ((GetAsyncKeyState(65)) && (!player->isMoving())) {	//	A
		if (passabilityMap[curPosPlayer.x-1][curPosPlayer.y] == 0) {
			player->move(MoveDirection::LEFT,speed);
		}
		else if ((passabilityMap[curPosPlayer.x-1][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x-2][curPosPlayer.y] == 0)) {
			passabilityMap[curPosPlayer.x-1][curPosPlayer.y] = 0;
			passabilityMap[curPosPlayer.x-2][curPosPlayer.y] = 1;
			mapObjects[curPosPlayer.x-1][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 2);
			mapObjects[curPosPlayer.x-2][curPosPlayer.y] = mapObjects[curPosPlayer.x-1][curPosPlayer.y];
			mapObjects[curPosPlayer.x-1][curPosPlayer.y] = nullptr;
			player->move(MoveDirection::LEFT, speed / 2);
			}
		//Двигаем 2 кубика
		else if ((passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x - 3][curPosPlayer.y] == 0)) {
			passabilityMap[curPosPlayer.x - 1][curPosPlayer.y] = 0;
			passabilityMap[curPosPlayer.x - 2][curPosPlayer.y] = 1;
			passabilityMap[curPosPlayer.x - 3][curPosPlayer.y] = 1;
			mapObjects[curPosPlayer.x - 2][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 4);
			mapObjects[curPosPlayer.x - 1][curPosPlayer.y]->move(MoveDirection::LEFT, speed / 4);
			mapObjects[curPosPlayer.x - 3][curPosPlayer.y] = mapObjects[curPosPlayer.x - 2][curPosPlayer.y];
			mapObjects[curPosPlayer.x - 2][curPosPlayer.y] = mapObjects[curPosPlayer.x - 1][curPosPlayer.y];
			mapObjects[curPosPlayer.x - 1][curPosPlayer.y] = nullptr;
			player->move(MoveDirection::LEFT, speed / 4);
		}
	}
	//D
	if ((GetAsyncKeyState(68)) && (!player->isMoving())) {
		if (passabilityMap[curPosPlayer.x+1][curPosPlayer.y] == 0) {
			player->move(MoveDirection::RIGHT,speed);
		}
		//Двигаем 1 кубик
		else if ((passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] == 0)) {

			passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] = 0;
			passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] = 1;
			mapObjects[curPosPlayer.x + 1][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 2);
			mapObjects[curPosPlayer.x + 2][curPosPlayer.y] = mapObjects[curPosPlayer.x + 1][curPosPlayer.y];
			mapObjects[curPosPlayer.x + 1][curPosPlayer.y] = nullptr;
			player->move(MoveDirection::RIGHT, speed / 2);
		}
		//Двигаем 2 кубика
		else if ((passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] == 1) and
			(passabilityMap[curPosPlayer.x + 3][curPosPlayer.y] == 0)) {
			passabilityMap[curPosPlayer.x + 1][curPosPlayer.y] = 0;
			passabilityMap[curPosPlayer.x + 2][curPosPlayer.y] = 1;
			passabilityMap[curPosPlayer.x + 3][curPosPlayer.y] = 1;
			mapObjects[curPosPlayer.x + 2][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 4);
			mapObjects[curPosPlayer.x + 1][curPosPlayer.y]->move(MoveDirection::RIGHT, speed / 4);
			mapObjects[curPosPlayer.x + 3][curPosPlayer.y] = mapObjects[curPosPlayer.x + 2][curPosPlayer.y];
			mapObjects[curPosPlayer.x + 2][curPosPlayer.y] = mapObjects[curPosPlayer.x + 1][curPosPlayer.y];
			mapObjects[curPosPlayer.x + 1][curPosPlayer.y] = nullptr;
			player->move(MoveDirection::RIGHT, speed / 4);
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