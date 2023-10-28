#include "Data.h"

float mCurrentTick=0.0;
Camera cam1(vec3(10,15,15));
int mSIMULATION_TIME = 20;
int myTick = 0;
vector<vec3> mTeapotColors;
vector<Object> GrObjects;
POINT MouseXY;

int SizeWindowX=1000;
int SizeWindowY=800;

void initData() {
	Object obj1, obj2, obj3, obj4,obj5;

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

	obj5.set_color(vec3(1, 1, 0));
	obj5.set_position(vec3(0, 0, 0));

	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);
	GrObjects.push_back(obj5);
}