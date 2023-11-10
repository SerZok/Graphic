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
	Object obj1, obj2, obj3, obj4;

	mLight.setAmbient(vec4(0, 0, 0, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(1, 1, 1, 1));
	mLight.setPosition(vec4(0, 10, 0, 1));

	vector< shared_ptr <PhongMaterial>> Materials;
	shared_ptr <PhongMaterial> pmat1,pmat2,pmat3,pmat4;

	pmat1 = make_shared <PhongMaterial>();
	pmat2 = make_shared <PhongMaterial>();
	pmat3 = make_shared <PhongMaterial>();
	pmat4 = make_shared <PhongMaterial>();
	pmat1->load("data//Materials//Material1.txt");
	pmat2->load("data//Materials//Material2.txt");
	pmat3->load("data//Materials//Material3.txt");
	pmat4->load("data//Materials//Material4.txt");
	Materials.push_back(pmat1);
	Materials.push_back(pmat2);
	Materials.push_back(pmat3);
	Materials.push_back(pmat4);

	vector<shared_ptr<Mesh>> meshes;
	shared_ptr <Mesh> mesh1, mesh2, mesh3, mesh4;

	mesh1 = make_shared <Mesh>();
	mesh2 = make_shared <Mesh>();
	mesh3 = make_shared <Mesh>();
	mesh4 = make_shared <Mesh>();
	mesh1->load("data//Meshes//Box.obj");
	//mesh2->load("data//Meshes//ChamferBox.obj");
	//mesh3->load("data//Meshes//SimplePlane.obj");
	//mesh4->load("data//Meshes//Sphere.obj");
	meshes.push_back(mesh1);
	meshes.push_back(mesh2);
	meshes.push_back(mesh3);
	meshes.push_back(mesh4);

	//mesh3.get()->Show();

	obj1.set_material(Materials[0]);
	obj1.set_mesh(meshes[0]);
	obj1.set_angle(180.0f);
	obj1.set_position(vec3(4, 0, 0));

	obj2.set_material(Materials[1]);
	obj2.set_angle(0.0f);
	obj2.set_position(vec3(-4, 0, 0));

	obj3.set_material(Materials[2]);
	obj3.set_angle(-90.0f);
	obj3.set_position(vec3(0, 0, 4));

	obj4.set_material(Materials[3]);
	obj4.set_angle(90.0f);
	obj4.set_position(vec3(0, 0, -4));

	GrObjects.push_back(obj1);
	GrObjects.push_back(obj2);
	GrObjects.push_back(obj3);
	GrObjects.push_back(obj4);
}