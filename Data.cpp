#include "Data.h"

int SizeWindowX=800;
int SizeWindowY=600;
int mCurrentTick=0;
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
unsigned int monsters_size=4;
vector <int> monstersLastDirection;
const int heightWall = 2, wall = 1, pass = 0;

bool deadend(int x, int y, int** maze, int height, int width) {
	int a = 0;
	if (x != 1) {
		if (maze[y][x - 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != 1) {
		if (maze[y - 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) {
		if (maze[y][x + 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != height - 2) {
		if (maze[y + 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (a == 4) return 1;
	else return 0;
}

//карта проходимости
int** passabilityMap;
//int passabilityMap[21][21] = {
//	 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
//	 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
//	 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
//	 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
//	 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
//	 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
//	 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
//	 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
//	 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
//	 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
//	 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
//	 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
//	 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
//	 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
//	 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
//	 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
//	 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
//	 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
//	 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
//	 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
//	 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
//};

void mazemake(int** maze, int height, int width) {
	int x, y, c, a;
	bool b;
	int generateWall;

	for (int i = 0; i < height; i++) // Массив заполняется стенами
		for (int j = 0; j < width; j++){
			if (i == 0 || j == 0 || i == 20 || j == 20){
				maze[i][j] = 3;
			}
			else{
				do{
					generateWall = rand() % 3;
				} while (generateWall == 0);

				if (generateWall == 1){
					int switchBlock = rand() % 5;
					if (switchBlock == 1 || switchBlock == 2 || switchBlock == 3)
						maze[i][j] = heightWall;
					else
						maze[i][j] = wall;
				}
				else if (generateWall == 2){
					maze[i][j] = heightWall;
				}
			}
		}

	x = 3; y = 3; a = 0;
	while (a < 1000) {
		maze[y][x] = pass; a++;
		while (1) { // Бесконечный цикл, который прерывается только тупиком
			c = rand() % 4;
			switch (c) {
			case 0: if (y != 1)
				if (maze[y - 2][x] == wall || maze[y - 2][x] == heightWall) { // Вверх
					maze[y - 1][x] = pass;
					maze[y - 2][x] = pass;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (maze[y + 2][x] == wall || maze[y + 2][x] == heightWall) { // Вниз
					maze[y + 1][x] = pass;
					maze[y + 2][x] = pass;
					y += 2;
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == wall || maze[y][x - 2] == heightWall) { // Налево
					maze[y][x - 1] = pass;
					maze[y][x - 2] = pass;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (maze[y][x + 2] == wall || maze[y][x + 2] == heightWall) { // Направо
					maze[y][x + 1] = pass;
					maze[y][x + 2] = pass;
					x += 2;
				}
			}
			if (deadend(x, y, maze, height, width))
				break;
		}

		if (deadend(x, y, maze, height, width)) // Вытаскиваем крота из тупика
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != pass);
	}
}

//рандомизация позиции монстров и героя
ivec2 rand_pos_monst() {
	int i = rand() % 20;
	int j = rand() % 20;
	if (passabilityMap[i][j] != 0)
		return rand_pos_monst();
	else
		return ivec2(i, j);
}

void initData() {
	srand(time(0));
	passabilityMap = new int* [21];
	for (int i = 0; i < 21; i++)
		passabilityMap[i] = new int[21];

	mazemake(passabilityMap, 21, 21);

	// ПОЛУЧЕНИЕ ИНФОРМАЦИИ ОБ OPENGL
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	//Свет
	mLight.setAmbient(vec4(0, 0, 0, 1));
	mLight.setDiffuse(vec4(1, 1, 1, 1));
	mLight.setSpecular(vec4(0, 0, 0, 1));
	mLight.setPosition(vec4(20, 30, 0, 1));

	planeTexture.load("data\\Textures\\maxresdefault.jpg");
	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data//GameObjectsDescription.json");

	shared_ptr<GameObject>monster;
	int i = 0;
	while (i != monsters_size) {
		monstersLastDirection.push_back(-1);
		ivec2 mPos = rand_pos_monst();
		passabilityMap[mPos.x][mPos.y] = 4;
		i++;
	}
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
			case 4:
				mapObjects[i][j]= gameObjectFactory.create(GameObjectType::MONSTER, i, j);
				monsters.push_back(mapObjects[i][j]);
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

	// инициализация плоскости
	planeGraphicObject.set_position(vec3(0, 0, 0));
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.set_mesh(planeMesh);
	shared_ptr<PhongMaterialWithTexture> planeMaterial = make_shared<PhongMaterialWithTexture>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.set_material(planeMaterial);
}