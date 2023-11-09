#include "Display.h"
#include "Data.h"
#include <string>

int init_time = time(NULL), final_time, FPS;

void getFPS() {
	final_time = time(NULL);
	if ((final_time - init_time) > 0)
		FPS = mCurrentTick / (final_time - init_time);
	char windowTitle[15];
	sprintf_s(windowTitle, 15, "FPS : %i", FPS);
	glutSetWindowTitle(windowTitle);
}

void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.1, 0.1, 0.2, 0.3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
<<<<<<< HEAD
	//getFPS();

	glEnable(GL_LIGHTING);

	cam1.apply();

	mLight.apply(GL_LIGHT0);
	
=======
	getFPS();
	mCam.apply();
	mLight.apply(GL_LIGHT0);


	//GrObjects[0].material->Show();
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
	for (auto& obj : GrObjects) { obj.draw(); }

	// смена переднего и заднего буферов
	glutSwapBuffers();
	mCurrentTick++;
};