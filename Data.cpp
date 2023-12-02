#include "Data.h"

int SizeWindowX=800;
int SizeWindowY=600;
int mCurrentTick=0;
int myTick = 0;
Camera cam1(vec3(0,1,50));
vector<vec3> mTeapotColors;
POINT MouseXY;
Light mLight;

// список игровых объектов расположенных на карте
shared_ptr<GameObject>mapObjects[21][21];
vector<shared_ptr<GameObject>>monsters;
shared_ptr<GameObject>player;

Object planeGraphicObject;//Для полскости
GameObjectFactory gameObjectFactory;

Texture planeTexture;

	// карта проходимости
int passabilityMap[21][21] = {
	 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
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



static ivec2 rand_pos_monst() {
	int i = rand() % 20;
	int j = rand() % 20;
	if (passabilityMap[i][j] != 0)
		return rand_pos_monst();
	else
		return ivec2(i, j);
}

//void rand_map(int height, int width, int** Map) {
//	for (int i = 1; i < height - 1; i++) {
//		for (int j = 1; j < width - 1; j++) {
//			if ((i % 2 != 0 && j % 2 != 0) && //если ячейка нечетная по x и y, 
//				(i < height && j < width - 1))   //и при этом находится в пределах стен лабиринта
//				passabilityMap[i][j] = 0;       //то это КЛЕТКА
//			else passabilityMap[i][j] = 1;           //в остальных случаях это СТЕНА.
//		}
//	}
//
//}

void initData() {
	srand(time(0));
	//rand_map(21, 21, passabilityMap);


	// ПОЛУЧЕНИЕ ИНФОРМАЦИИ ОБ OPENGL
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	//Свет
	mLight.setAmbient(vec4(0, 0, 0, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(0, 0, 0, 1));
	mLight.setPosition(vec4(20, 30, 0, 1));

	planeTexture.load("data\\Textures\\vlcsnap_2023_12_01_10h37m31s394.0.jpg");
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
	ivec2 pcPos = rand_pos_monst();
	player = gameObjectFactory.create(GameObjectType::PLAYER, pcPos.x, pcPos.y);

	shared_ptr<GameObject>monster;
	while(monsters.size()!=3){
		ivec2 mPos = rand_pos_monst();
		monster= gameObjectFactory.create(GameObjectType::MONSTER, mPos.x, mPos.y);
		monsters.push_back(monster);
	}
	// инициализация плоскости
	planeGraphicObject.set_position(vec3(0, 0, 0));
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.set_mesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.set_material(planeMaterial);
}