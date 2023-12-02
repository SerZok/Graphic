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
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(pos);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = pos;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));

	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}