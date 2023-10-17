#include "Camera.h"

void Camera::apply() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	recalcPos(r,angleX,angleY);
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalcPos(float _r, float _o, float _fi) {
	position.x = _r * sin(_o) * cos(_fi);
	position.y = _r * sin(_o) * cos(_fi);
	position.z = _r * cos(_o);
}