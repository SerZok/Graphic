#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <fstream>
#include <string>

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
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	void load(std::string filename);
	void apply();
};
