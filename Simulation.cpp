#include "Data.h"
#include "Simulation.h"
#include <time.h>


float getSimulationTime() {
	int last_time = clock();
	float simulationTime = float(clock() - last_time) / CLOCKS_PER_SEC;
	last_time = clock();
	return 0.01f;
}

void cameraSimulation(float simulationTime) {
	if (GetAsyncKeyState(VK_LBUTTON)) {
		int CenterW = glutGet(GLUT_WINDOW_WIDTH) / 2;
		int CenertH = glutGet(GLUT_WINDOW_HEIGHT) / 2;

		float mAngleX = CenterW - MouseXY.x;
		float mAngleY = CenertH - MouseXY.y;
		float speed = 0.003;

		if (GetCursorPos(&MouseXY)) {
			cam1.rotateLeftRight(mAngleX * speed);
			cam1.rotateUpDown(mAngleY * speed);
			SetCursorPos(MouseXY.x, MouseXY.y);
		}
	}
	if (GetAsyncKeyState(VK_LEFT))		cam1.rotateLeftRight(0.3);
	if (GetAsyncKeyState(VK_RIGHT))		cam1.rotateLeftRight(-0.3);
	if (GetAsyncKeyState(VK_ADD))		cam1.zoomInOut(-0.2);
	if (GetAsyncKeyState(VK_SUBTRACT))	cam1.zoomInOut(0.2);
	if (GetAsyncKeyState(VK_UP))		cam1.rotateUpDown(-0.2);
	if (GetAsyncKeyState(VK_DOWN))		cam1.rotateUpDown(0.2);
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

	if ((GetAsyncKeyState(68)) && (!player->isMoving())) {	//	W
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