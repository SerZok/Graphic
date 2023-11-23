#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Camera.h"
#include "Light.h"
#include "GameObjectFactory.h"

extern float mCurrentTick;
extern int SizeWindowX;
extern int SizeWindowY;
extern int myTick;
extern int passabilityMap[21][21];

extern Camera cam1;
extern POINT MouseXY;
extern Light mLight;
extern Object planeGraphicObject;
extern vector<vec3> mTeapotColors;
extern vector<shared_ptr<Mesh>> Meshes;
extern vector< shared_ptr <PhongMaterial>> Materials;
extern shared_ptr<GameObject>mapObjects[21][21];

void initData();