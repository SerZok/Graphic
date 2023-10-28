#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Camera.h"
#include "Object.h"

extern float mCurrentTick;

extern vector<vec3> mTeapotColors;
extern vector<Object> GrObjects;
extern Camera cam1;
extern POINT MouseXY;
extern int SizeWindowX;
extern int SizeWindowY;


extern int myTick;

void initData();
