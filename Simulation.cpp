#include "Simulation.h"
#include "Data.h"


void simulation() {
	glutPostRedisplay();
	if (GetAsyncKeyState(VK_LBUTTON)) {
		int CenterW= glutGet(GLUT_WINDOW_WIDTH)/2;
		int CenertH= glutGet(GLUT_WINDOW_HEIGHT)/2;

		float mAngleX = CenterW - MouseXY.x;
		float mAngleY = CenertH - MouseXY.y;
		float speed = 0.005;

		if (GetCursorPos(&MouseXY)) {
			cam1.rotateLeftRight(mAngleX*speed);
			cam1.rotateUpDown(mAngleY*speed);
			SetCursorPos(MouseXY.x, MouseXY.y);
		}
	}

	if (GetAsyncKeyState(VK_LEFT))		cam1.rotateLeftRight(0.5);
	if (GetAsyncKeyState(VK_RIGHT))		cam1.rotateLeftRight(-0.5);
	if (GetAsyncKeyState(VK_ADD))		cam1.zoomInOut(-0.5);
	if (GetAsyncKeyState(VK_SUBTRACT))	cam1.zoomInOut(0.5);
	if (GetAsyncKeyState(VK_UP))		cam1.rotateUpDown(-0.8);
	if (GetAsyncKeyState(VK_DOWN))		cam1.rotateUpDown(0.8);
};