#include "Simulation.h"
#include "Data.h"


void simulation() {
	glutPostRedisplay();
	if (GetAsyncKeyState(VK_LBUTTON)) {
		if (GetCursorPos(&MouseXY)) {
			mCam.rotateLeftRight(float(SizeWindowX - MouseXY.x) / (SizeWindowX));
			mCam.rotateUpDown(float(SizeWindowY - MouseXY.y) / (SizeWindowY));
			SetCursorPos(MouseXY.x, MouseXY.y);
		}
	}

	if (GetAsyncKeyState(VK_LEFT))		mCam.rotateLeftRight(0.5);
	if (GetAsyncKeyState(VK_RIGHT))		mCam.rotateLeftRight(-0.5);
	if (GetAsyncKeyState(VK_ADD))		mCam.zoomInOut(-0.5);
	if (GetAsyncKeyState(VK_SUBTRACT))	mCam.zoomInOut(0.5);
	if (GetAsyncKeyState(VK_UP))		mCam.rotateUpDown(-0.8);
	if (GetAsyncKeyState(VK_DOWN))		mCam.rotateUpDown(0.8);
};