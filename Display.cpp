#include "Data.h"
#include "Display.h"


int final_time, FPS, init_time = time(NULL);

// вывод горизонтальной плоскости (основание уровня)
void drawPlane() {
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном текстурном блоке
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку
	planeTexture.apply();
	// указываем режим наложения текстуры (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// выводим плоскость
	planeGraphicObject.draw();
	// отключаем текстурирование (чтобы все остальные объекты выводились без текстур)
	Texture::disableAll();
}

void getFPS() {
	FPS = mCurrentTick / (final_time - init_time);
	init_time = time(NULL);
	char windowTitle[50];
	sprintf_s(windowTitle, 50, "made by SergeyZ FPS : %i", mCurrentTick);
	glutSetWindowTitle(windowTitle);
	mCurrentTick = 0;
}

void display(){
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.7, 0.7, 0.7, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	mCurrentTick++;
	if ((final_time - init_time) >= 1) {
		getFPS();
	}
	cam1.apply();
	mLight.apply(GL_LIGHT0);
	drawPlane();

	if (player!=nullptr)
		player->draw();

	if (drawBomb)
		bomb->draw();

	/*for (auto mons : monsters)
		mons->draw();*/

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr){
				mapObjects[i][j]->draw();
			}
		}
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
	final_time = time(NULL);
};