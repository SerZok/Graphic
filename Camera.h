#include <windows.h>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

using namespace std;
using namespace glm;

class Camera {
	vec3 pos;
	float r, o, fi;
public:
	Camera(vec3 po):pos(po) {}
	void recalcPos(float ,float , float );
	void apply();
};