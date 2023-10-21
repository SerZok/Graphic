#include "Data.h"

vec3 positionC(20, 15, 10);
int mCurrentTick=0;
Camera cam1(positionC);
int mSIMULATION_TIME = 20;
float myTick = 0.0f;
vector<vec3> mTeapotColors;
vector<Object> GrObjects;


void initData() {
	Object obj1, obj2, obj3, obj4;

	obj1.set_color(vec3(1, 0, 0));	//�������
	obj1.set_angle(180.0f);
	obj1.set_position(vec3(4, 0, 0));

	obj2.set_color(vec3(0, 1, 0));	//�������
	obj2.set_angle(0.0f);
	obj2.set_position(vec3(-4, 0, 0));

	obj3.set_color(vec3(0, 0, 1));	//�����
	obj3.set_angle(-90.0f);
	obj3.set_position(vec3(0, 0, 4));

	obj4.set_color(vec3(1, 1, 1));	//�����
	obj4.set_angle(90.0f);
	obj4.set_position(vec3(0, 0, -4));

	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);
}