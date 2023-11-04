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
	vec4 ambient;	// ������� ������������
	vec4 diffuse;	// ��������� ������������
	vec4 specular;	// ���������� ������������
	vec4 emission;	// ������������
	float shininess;// ������� ����������������

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
