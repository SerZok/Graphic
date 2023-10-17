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
	vec3 position;
	float r, angleX, angleY;
	void recalcPos(float ,float , float );
public:
	Camera(vec3 po):position(po) {}
	void apply();
	void setPosition(vec3 pos) { position = pos; };
	vec3 getPostion() { return position; };

	void rotateLR(float degree);
	void rotateUD(float degree);
	void zoomIO(float distance);

};