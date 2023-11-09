#include <windows.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Display.h"
#include "Data.h"
#include "Simulation.h"

using namespace std;
using namespace glm;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h){
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y) {
	//printf("Key code is %i\n", key);
	std::cout << "KEY: " << (short)key << " " << key << "\n";
};

int main(int argc, char** argv){
	setlocale(LC_ALL, "ru");

<<<<<<< HEAD
	//PhongMaterial  mat1;
	//mat1.load("Materials\\test.txt");
	//mat1.apply();

=======
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(SizeWindowX, SizeWindowY);
	glutCreateWindow("AOKG");

	initData();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);

	glutMainLoop();

	return 0;
};