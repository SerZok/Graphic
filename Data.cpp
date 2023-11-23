#include "Data.h"

int SizeWindowX=800;
int SizeWindowY=600;
float mCurrentTick=0.0;
int myTick = 0;
Camera cam1(vec3(50,1,0));
vector<vec3> mTeapotColors;
POINT MouseXY;
Light mLight;

// список игровых объектов расположенных на карте
shared_ptr<GameObject>mapObjects[21][21];
shared_ptr<GameObject>player;

Object planeGraphicObject;//Для полскости

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
GameObjectFactory gameObjectFactory;

void initData() {
	//Свет
	mLight.setAmbient(vec4(0, 0, 0, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(0, 0, 0, 1));
	mLight.setPosition(vec4(20, 30, 0, 1));

	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data//GameObjectsDescription.json");
	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}
	// инициализация главного героя
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 1);
	// инициализация плоскости
	planeGraphicObject.set_position(vec3(0, 0, 0));
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.set_mesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.set_material(planeMaterial);


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

	//for (int i = 0; i < 21; i++) {
	//	for (int j = 0; j < 21; j++) {
	//		if (passabilityMap[i][j] == 0) {
	//			mapObjects[i][j] = nullptr;
	//			planeGrObject.set_material(Materials[3]);
	//		}
	//		else if (passabilityMap[i][j] == 1) {//ChamferBox
	//			mapObjects[i][j] = make_shared<GameObject>();
	//			ChamferBox.set_material(Materials[2]);
	//			mapObjects[i][j]->setGraphicObject(ChamferBox);
	//			mapObjects[i][j]->setPosition(i, j);
	//		}
	//		else if(passabilityMap[i][j] == 2){//simple box
	//			mapObjects[i][j] = make_shared<GameObject>();
	//			Box.set_material(Materials[1]);
	//			mapObjects[i][j]->setGraphicObject(Box);
	//			mapObjects[i][j]->setPosition(i, j);
	//		}
	//		else if (passabilityMap[i][j] == 3) {//crainiy box
	//			mapObjects[i][j] = make_shared<GameObject>();
	//			Box.set_material(Materials[0]);
	//			mapObjects[i][j]->setGraphicObject(Box);
	//			mapObjects[i][j]->setPosition(i, j);
	//		}
	//		
	//	}
}