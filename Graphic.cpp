#include <windows.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Object.h"

using namespace std;
using namespace glm;

const int mSIMULATION_TIME = 10;

int mCurrentTick = 0;

vector<vec3> mTeapotColors;
vector<Object> GrObjects;
Object obj_test;

char mCurrentScalar = 0;
float myTick = 0.0f;

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна и по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-15, 15, 20, 0, 0, 0, 0, 1, 0);

	//vec3 c = mTeapotColors[mCurrentScalar];
	//glColor3f(c.r, c.g, c.b);
	//glutWireTeapot(1);

	for (auto& obj : GrObjects) {
		obj.draw();
	}
	obj_test.draw();

	// смена переднего и заднего буферов
	glutSwapBuffers();
	mCurrentTick++;
};

// функция вызывается каждые 20 мс
void simulation(int value) {
	if (mCurrentScalar < mTeapotColors.size() - 1) {
		mCurrentScalar++;
	}
	else mCurrentScalar = 0;

	glutPostRedisplay();
	glutTimerFunc(mSIMULATION_TIME, simulation, 0);

	obj_test.set_angle(myTick);
	myTick++;
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y) {
	//printf("Key code is %i\n", key);
	std::cout << "KEY: " << (short)key << " " << key << "\n";
	if (mTeapotColors.size() + 48 >= key && key >= 49) {
		mCurrentScalar = key - 49;
		return;
	}
};


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Teapot");


	Object obj1, obj2, obj3, obj4;

	obj1.set_color(vec3(1, 0, 0));	//Красный
	obj1.set_angle(180.0f);
	obj1.set_position(vec3(4, 0, 0));

	obj2.set_color(vec3(0, 1, 0));	//Зеленый
	obj2.set_angle(0.0f);
	obj2.set_position(vec3(-4, 0, 0));

	obj3.set_color(vec3(0, 0, 1));	//Синий
	obj3.set_angle(-90.0f);
	obj3.set_position(vec3(0, 0, 4));

	obj4.set_color(vec3(1, 1, 1));	//Белый
	obj4.set_angle(90.0f);
	obj4.set_position(vec3(0, 0, -4));

	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);

	obj_test.set_color(vec3(0, 1, 1));


	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	glutTimerFunc(mSIMULATION_TIME, simulation, 0);
	//glutKeyboardFunc(keyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();

	return 0;
};