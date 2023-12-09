#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include "glew.h"

#include "Camera.h"
#include "Light.h"
#include "GameObjectFactory.h"

extern int mCurrentTick;
extern int SizeWindowX;
extern int SizeWindowY;
extern int passabilityMap[21][21];

extern Camera cam1;
extern POINT MouseXY;
extern Light mLight;
extern Object planeGraphicObject;
extern Texture planeTexture;
extern vector<vec3> mTeapotColors;
extern vector<shared_ptr<Mesh>> Meshes;
extern vector< shared_ptr <PhongMaterial>> Materials;
extern shared_ptr<GameObject>mapObjects[21][21];
extern shared_ptr<GameObject>player;
extern vector<shared_ptr<GameObject>>monsters;
extern vector <int> monstersLastDirection;

void initData();