#include "Display.h"
#include "Data.h"
#include <string>

int init_time = time(NULL),final_time,FPS;

void getFPS() {
	final_time = time(NULL);
	if ((final_time - init_time) > 0)
		FPS = mCurrentTick / (final_time - init_time);
	char windowTitle[10];
	sprintf_s(windowTitle, 10, "FPS %i", FPS);
	glutSetWindowTitle(windowTitle);
}
void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	getFPS();
	cam1.apply();

	for (auto& obj : GrObjects) { obj.draw(); }

	// ����� ��������� � ������� �������
	glutSwapBuffers();
	mCurrentTick++;

};