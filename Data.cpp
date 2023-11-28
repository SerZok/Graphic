#include "Data.h"

int SizeWindowX=800;
int SizeWindowY=600;
int mCurrentTick=0;
int myTick = 0;
Camera cam1(vec3(50,1,0));
vector<vec3> mTeapotColors;
POINT MouseXY;
Light mLight;

// список игровых объектов расположенных на карте
shared_ptr<GameObject>mapObjects[21][21];
vector<shared_ptr<Mesh>> Meshes;
vector<shared_ptr<PhongMaterial>> Materials;
Object planeGrObject;//Для полскости

	// карта проходимости
int passabilityMap[21][21] = {
	 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,4,0,3,
	 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
	 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
	 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
	 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
	 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
	 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
	 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
	 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
	 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
	 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
	 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
	 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
	 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
	 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
	 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
	 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
	 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
	 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
	 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	};

void initData() {
	//Свет
	mLight.setAmbient(vec4(0, 0, 0, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(1, 1, 1, 1));
	mLight.setPosition(vec4(0, 20, 0, 1));
	 
	//Материал
	shared_ptr <PhongMaterial> pmat1,pmat2,pmat3, pmat4, pmat5;
	pmat1 = make_shared <PhongMaterial>();
	pmat2 = make_shared <PhongMaterial>();
	pmat3 = make_shared <PhongMaterial>();
	pmat4 = make_shared <PhongMaterial>();
	pmat5 = make_shared <PhongMaterial>();
	pmat1->load("data//Materials//Border.txt");
	pmat2->load("data//Materials//Box.txt");
	pmat3->load("data//Materials//ChamferBox.txt");
	pmat4->load("data//Materials//Plane.txt");
	pmat5->load("data//Materials//Sphere.txt");
	Materials.push_back(pmat1);
	Materials.push_back(pmat2);
	Materials.push_back(pmat3);
	Materials.push_back(pmat4);
	Materials.push_back(pmat5);

	//Меши
	shared_ptr <Mesh> mesh1, mesh2, mesh3, mesh4;
	mesh1 = make_shared <Mesh>();
	mesh2 = make_shared <Mesh>();
	mesh3 = make_shared <Mesh>();
	mesh4 = make_shared <Mesh>();
	mesh1->load("data//Meshes//Box.obj");
	mesh2->load("data//Meshes//ChamferBox.obj");
	mesh3->load("data//Meshes//SimplePlane.obj");
	mesh4->load("data//Meshes//Sphere.obj");
	Meshes.push_back(mesh1);
	Meshes.push_back(mesh2);
	Meshes.push_back(mesh3);
	Meshes.push_back(mesh4);

	Object Box, ChamferBox, Sphere;

	Box.set_mesh(Meshes[0]);
	ChamferBox.set_mesh(Meshes[1]);
	planeGrObject.set_mesh(Meshes[2]);
	Sphere.set_mesh(Meshes[3]);
	Sphere.set_material(Materials[3]);
	Sphere.set_position(vec3(0, 0, 0));

	/*
	pmat1->load("data//Materials//Border.txt");			0
	pmat2->load("data//Materials//Box.txt");			1
	pmat3->load("data//Materials//ChamferBox.txt");		2
	pmat4->load("data//Materials//Plane.txt");			3
	pmat5->load("data//Materials//Sphere.txt");			4

	else if (passabilityMap[i][j] == 4) {
				mapObjects[i][j] = make_shared<GameObject>();
				mapObjects[i][j]->setGraphicObject(Sphere);
				mapObjects[i][j]->setPosition(j, i);
			}
	*/

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (passabilityMap[i][j] == 0) {
				mapObjects[i][j] = nullptr;
				planeGrObject.set_material(Materials[3]);
			}
			else if (passabilityMap[i][j] == 1) {//ChamferBox
				mapObjects[i][j] = make_shared<GameObject>();
				ChamferBox.set_material(Materials[2]);
				mapObjects[i][j]->setGraphicObject(ChamferBox);
				mapObjects[i][j]->setPosition(i, j);
			}
			else if(passabilityMap[i][j] == 2){//simple box
				mapObjects[i][j] = make_shared<GameObject>();
				Box.set_material(Materials[1]);
				mapObjects[i][j]->setGraphicObject(Box);
				mapObjects[i][j]->setPosition(i, j);
			}
			else if (passabilityMap[i][j] == 3) {//crainiy box
				mapObjects[i][j] = make_shared<GameObject>();
				Box.set_material(Materials[0]);
				mapObjects[i][j]->setGraphicObject(Box);
				mapObjects[i][j]->setPosition(i, j);
			}
			
		}
	}

}