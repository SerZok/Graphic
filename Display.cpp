#include "Display.h"
#include "Data.h"

void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-15, 15, 20, 0, 0, 0, 0, 1, 0);
	*/
	cam1.apply();

	for (auto& obj : GrObjects) {
		obj.draw();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
	mCurrentTick++;
};