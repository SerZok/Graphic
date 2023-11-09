#include "Object.h"
Object::Object() {
	material=nullptr;
	position = vec3(0, 0, 0);
	angle = 0;
	color = vec3(0, 0, 0);
}

<<<<<<< HEAD
void Object:: set_material( shared_ptr <PhongMaterial> mat) {
	cout << material<<' '<<mat<<endl;
	material = mat;
=======
void Object:: set_material(PhongMaterial* mat) {
	material = mat;
	material->apply();
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
}

void Object::draw() {
	glColor3f(color.r, color.g, color.b);
<<<<<<< HEAD

	if (material!=nullptr) material->apply();

=======
	
	if (material != nullptr) {
		//material->apply();
	}
	
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
	glPushMatrix();
	recalculateModelMatrix();
	glMultMatrixf(modelMatrix);
	glutSolidTeapot(1.0);
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

void Object::set_angle(float rad) { Object::angle = rad; }
void Object::set_color(vec3 color) {Object::color = color;}
void Object::set_position(vec3 position) {
	Object::position = position;
	recalculateModelMatrix();
}

float Object::get_angle() {	return Object::angle;}
vec3 Object::get_color() {	return Object::color;}
vec3 Object::get_position() {	return Object::position;}