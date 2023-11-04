#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PhongMaterial.h"

using namespace glm;
// ����� ��� ������������� ������ ������������ �������

class Object {
private:
	vec3 position;
	float angle;
	vec3 color;
	PhongMaterial* material;

	GLfloat modelMatrix[16] = {
		 1.0, 0.0, 0.0, 0.0, // ��� Ox
		 0.0, 1.0, 0.0, 0.0, // ��� Oy
		 0.0, 0.0, 1.0, 0.0, // ��� Oz
		 0.0, 0.0, 0.0, 1.0 // ������� ������� (������ ������� ���������)
	};
	void recalculateModelMatrix();
public:

	Object();
	void set_angle(float grad);
	void set_position(vec3 postition);
	void set_color(vec3 color);
	void draw();
	vec3 get_position();
	vec3 get_color();
	float get_angle();
	void set_material(PhongMaterial *);
};