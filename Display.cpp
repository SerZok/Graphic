#include "Display.h"
#include "Data.h"

void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-15, 15, 20, 0, 0, 0, 0, 1, 0);
	*/
	cam1.apply();

	for (auto& obj : GrObjects) {
		obj.draw();
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();
	mCurrentTick++;
};