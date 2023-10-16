#include "Camera.h"

void Camera::apply() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	recalcPos(r,o,fi);
	gluLookAt(pos.x, pos.y, pos.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalcPos(float _r, float _o, float _fi) {
	pos.x = _r * sin(_o) * cos(_fi);
	pos.y = _r * sin(_o) * cos(_fi);
	pos.z = _r * cos(_o);
}