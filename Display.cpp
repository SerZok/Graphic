#include "Display.h"
#include "Data.h"

void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	cam1.apply();

	for (auto& obj : GrObjects) {
		obj.draw();
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();
	mCurrentTick++;
};