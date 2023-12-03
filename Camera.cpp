#include "Camera.h"

Camera::Camera(){
	position = vec3(0, 0, 0);
	Point = vec3(10, 0, 0);
	r = 1.0f;
	angleX = 0.0f;
	angleY = 0.0f;
}

Camera::Camera(vec3 pos) {
	setPosition(pos);
}

void Camera::apply() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, Point.x, Point.y, Point.z, 0, 1, 0);
}

void Camera::setPoint(vec3 point) {
	Point = point;
}

void Camera::recalculatePosition(){
	float rad_y = radians(angleY);
	float rad_x = radians(angleX);
	position.x = r * sin(rad_y) * cos(rad_x);
	position.y = r * cos(rad_y);
	position.z = r * sin(rad_y) * sin(rad_x);
}

void Camera::rotateLeftRight(float degree){
	angleX += degree;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree){
	angleY += degree;
	if (angleY < 5) angleY = 5;
	if (angleY > 150) angleY = 150;
	recalculatePosition();
}

void Camera::zoomInOut(float distance){
	r += distance;
	if (r > 60) r = 60;
	if (r < 5) r = 5;
	recalculatePosition();
}

void Camera::setPosition(vec3 pos) {
	// ���������� ������ - ���������� �� ������ ������� ��������� �� �������� �������
	r = length(pos);
	// ���������� ������������ ����:
	// ��� ���� ����� �������� �� ������ ��������� � ����������� (v1)
	// � ��������� ����� ������� �� �������������� ��������� (v2)
	// ��� ����������� ���� ������������ ��������� ������������ ��������������� ��������
	vec3 v1 = pos;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// ����������� ������� ���������� �������������� ����:
	// ��� ���� ����� ��������� (v2) � ��������� �������� ����� ��� Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));

	// ������������� ������� (��� ������������� ������ ����������)
	recalculatePosition();
}