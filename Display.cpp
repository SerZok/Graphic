#include "Display.h"
#include "Data.h"
#include <string>

int init_time = time(NULL),final_time, FPS;

void getFPS() {
	final_time = time(NULL);
	if ((final_time - init_time) > 0.0) 
		FPS = mCurrentTick / (final_time - init_time);
	char windowTitle[15];
	sprintf_s(windowTitle, 15, "FPS : %i", FPS);
	glutSetWindowTitle(windowTitle);
}

void display(){
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.1, 0.1, 0.2, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	getFPS();

	cam1.apply();
	mLight.apply(GL_LIGHT0);

	for (auto& obj : GrObjects) { 
		obj.set_angle(cam1.getAngleX());//Чайники смотрят в камеру отосительно X
		obj.draw(); 
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
	mCurrentTick++;
};