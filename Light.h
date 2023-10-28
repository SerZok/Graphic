#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

using namespace std;
using namespace glm;

class Light {
private:
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
public:
	Light();
	Light(vec3);
	Light(float,float,float);
	
	void setPosition(vec3);
	void setAmbient(vec4);
	void setDiffuse(vec4);
	void setSpecular(vec4);

	// установка всех параметров источника света с заданным номером
	// данная функция должна вызываться после установки камеры,
	// т.к. здесь устанавливается позиция источника света
	void apply(GLenum LightNumber = GL_LIGHT0);
};