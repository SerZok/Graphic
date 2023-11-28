#include "Display.h"
#include "Data.h"


int init_time,final_time, FPS;

void getFPS() {
	FPS = mCurrentTick / (final_time - init_time);
	init_time = time(NULL);
	char windowTitle[15];
	sprintf_s(windowTitle, 15, "FPS : %i", mCurrentTick);
	glutSetWindowTitle(windowTitle);
	mCurrentTick = 0;
}

void display(){
	
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.1, 0.1, 0.2, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	mCurrentTick++;
	if ((final_time - init_time) >= 1) {
		getFPS();
	}


	cam1.apply();
	mLight.apply(GL_LIGHT0);
	planeGrObject.draw();

	//for (auto& obj : GrObjects) { obj.draw(); }
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr)
			{
				mapObjects[i][j]->draw();
			}
		}
	}


	// смена переднего и заднего буферов
	glutSwapBuffers();
	final_time = time(NULL);
};