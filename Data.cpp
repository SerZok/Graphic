#include "Data.h"

float mCurrentTick=0.0;
Camera cam1(vec3(10,15,15));
int myTick = 0;
vector<vec3> mTeapotColors;
vector<Object> GrObjects;
POINT MouseXY;
Light mLight;

int SizeWindowX=800;
int SizeWindowY=600;


void initData() {
	Object obj1, obj2, obj3, obj4,obj5;

	mLight.setAmbient(vec4(1, 1, 1, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(1, 1, 1, 1));
	mLight.setPosition(vec4(0, 10, 0, 1));

	PhongMaterial mat1, mat2, mat3, mat4;

	vector< shared_ptr <PhongMaterial>> Materials;

	shared_ptr <PhongMaterial> pmat1,pmat2,pmat3,pmat4;
	pmat1 = make_shared <PhongMaterial>();
	pmat2 = make_shared <PhongMaterial>();
	pmat3 = make_shared <PhongMaterial>();
	pmat4 = make_shared <PhongMaterial>();

	pmat1->load("Materials//Material1.txt");
	pmat2->load("Materials//Material2.txt");
	pmat3->load("Materials//Material3.txt");
	pmat4->load("Materials//Material4.txt");

	Materials.push_back(pmat1);
	Materials.push_back(pmat2);
	Materials.push_back(pmat3);
	Materials.push_back(pmat4);

	obj1.set_material(Materials[0]);
	//mat1.setDiffuse (vec4(0, 1, 0, 1));
	obj1.set_color(vec3(1, 0, 0));	//Красный
	obj1.set_angle(180.0f);
	obj1.set_position(vec3(4, 0, 0));

	obj2.set_material(Materials[1]);
	//mat2.setDiffuse (vec4(1, 0, 0, 1));
	//obj2.set_color(vec3(0, 1, 0));	//Зеленый
	obj2.set_angle(0.0f);
	obj2.set_position(vec3(-4, 0, 0));

	obj3.set_material(Materials[2]);
	//obj3.set_color(vec3(0, 0, 1));	//Синий
	obj3.set_angle(-90.0f);
	obj3.set_position(vec3(0, 0, 4));

	obj4.set_material(Materials[3]);
	//obj4.set_color(vec3(1, 1, 1));	//Белый
	obj4.set_angle(90.0f);
	obj4.set_position(vec3(0, 0, -4));

	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);

}