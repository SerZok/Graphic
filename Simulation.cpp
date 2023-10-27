#include "Simulation.h"
#include "Data.h"


void simulation() {
	glutPostRedisplay();
	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (GetCursorPos(&MouseXY)) {
			cam1.rotateLeftRight((SizeWindowX - MouseXY.x) / SizeWindowX/4);
			cam1.rotateUpDown((SizeWindowY - MouseXY.y) / SizeWindowY/4);
			SetCursorPos(MouseXY.x, MouseXY.y);
		}
	}

	if (GetAsyncKeyState(VK_LEFT)) cam1.rotateLeftRight(0.2);
	if (GetAsyncKeyState(VK_RIGHT)) cam1.rotateLeftRight(-0.2);
	if (GetAsyncKeyState(VK_ADD)) cam1.zoomInOut(-0.2);
	if (GetAsyncKeyState(VK_SUBTRACT)) cam1.zoomInOut(0.2);
	if (GetAsyncKeyState(VK_UP)) cam1.rotateUpDown(-0.2);
	if (GetAsyncKeyState(VK_DOWN)) cam1.rotateUpDown(0.2);
};