#include "Object.h"

void Object::draw() {
	glColor3f(color.r, color.g, color.b);
	glPushMatrix();
	recalculateModelMatrix();
	glMultMatrixf(modelMatrix);
	glutWireTeapot(1.0);
	glPopMatrix();
}

//������ ������� �� ������ position and angle
void Object::recalculateModelMatrix() {
	modelMatrix[12] = position.x;
	modelMatrix[13] = position.y;
	modelMatrix[14] = position.z;

	float rad = angle * 3.14159 / 180;

	modelMatrix[0] = cos(rad);
	modelMatrix[2] = sin(rad);
	modelMatrix[8] = -sin(rad);
	modelMatrix[10] = cos(rad);
}

void Object::set_angle(float rad) {
	Object::angle = rad;
}

void Object::set_color(vec3 color) {
	Object::color = color;
}

void Object::set_position(vec3 position) {
	Object::position = position;
	recalculateModelMatrix();
}

float Object::get_angle() {
	return Object::angle;
}

vec3 Object::get_color() {
	return Object::color;
}

vec3 Object::get_position() {
	return Object::position;
}