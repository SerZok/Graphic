#include "Data.h"
#include "Simulation.h"

float getSimulationTime() {
	return float(10.0f);
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

void gameObjectSimulation(float simulationTime) {

}

void movePlayer() {

}

void simulation() {
	float simualtionTime = getSimulationTime();
	cameraSimulation(simualtionTime);
	gameObjectSimulation(simualtionTime);
	movePlayer();
	glutPostRedisplay();
};