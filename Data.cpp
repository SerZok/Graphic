#include "Data.h"

Camera mCam(vec3(10,15,15));
vector<vec3> mTeapotColors;
vector<Object> GrObjects;
POINT MouseXY;
Light mLight;

float mCurrentTick=0.0;
int SizeWindowX=800;
int SizeWindowY=600;


void initData() {

	PhongMaterial mat1, mat2, mat3, mat4;
	mat1.load("Materials//Material1.txt");
	mat2.load("Materials//Material2.txt");
	mat3.load("Materials//Material3.txt");
	mat4.load("Materials//Material4.txt");

	mLight.setPosition(vec4(0, 20, 0, 1));

	Object obj1, obj2, obj3, obj4,obj5;
	obj1.set_material(&mat1);
	obj1.set_color(vec3(1, 0, 0));	//Красный
	obj1.set_angle(180.0f);
	obj1.set_position(vec3(4, 0, 0));

	obj2.set_material(&mat2);
	//obj2.set_color(vec3(0, 1, 0));	//Зеленый
	obj2.set_angle(0.0f);
	obj2.set_position(vec3(-4, 0, 0));

	obj3.set_material(&mat3);
	//obj3.set_color(vec3(0, 0, 1));	//Синий
	obj3.set_angle(-90.0f);
	obj3.set_position(vec3(0, 0, 4));

	obj4.set_material(&mat4);
	//obj4.set_color(vec3(1, 1, 1));	//Белый
	obj4.set_angle(90.0f);
	obj4.set_position(vec3(0, 0, -4));

	


	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);
	//GrObjects.push_back(obj5);
}