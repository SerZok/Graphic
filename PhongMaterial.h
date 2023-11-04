#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace glm;

class PhongMaterial{
private:
	vec4 ambient;	// фонова€ составл€юща€
	vec4 diffuse;	// диффузна€ составл€юща€
	vec4 specular;	// зеркальна€ составл€юща€
	vec4 emission;	// самосвечение
	float shininess;// степень отполированности

public:
	PhongMaterial();
	void setAmbient(vec4);
	void setDiffuse(vec4);
	void setSpecular(vec4);
	void setEmission(vec4);
	void setShininess(float );
	void load(std::string filename);
	void apply(void);
};
