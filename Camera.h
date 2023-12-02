#include <windows.h>
#include <iostream>
#include <vector>

#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

using namespace std;
using namespace glm;

class Camera {
	vec3 position;
	vec3 Point;
	float r, angleX, angleY;
	void recalculatePosition();
public:
	Camera();
	Camera(vec3 pos);
	void apply();
	vec3 getPostion() { return position; };
	void setPosition(vec3 pos);
	void setPoint(vec3 point);

	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);

};