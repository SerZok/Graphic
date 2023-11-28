#include <windows.h>
#include <iostream>
#include <vector>
#include "glew.h"

#include "Data.h"
#include "Display.h"
#include "Simulation.h"

using namespace std;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h){
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

int main(int argc, char** argv){
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(SizeWindowX, SizeWindowY);
	glutCreateWindow("AOKG");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	// проверка поддержки расширения для работы с буфером VBO
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported");
	};

	initData();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);
	glutMainLoop();



	return 0;
};