#include "Light.h"

Light::Light() {
	position =	vec4(0, 0, 0, 1);
	ambient  =	vec4(1, 1, 1, 1);
	diffuse  =	vec4(1, 1, 1, 1);
	specular =	vec4(1, 1, 1, 1);
}

Light::Light(vec3 pos) {
	position =	vec4(pos,1);
	ambient  =	vec4(1, 1, 1, 1);
	diffuse  =	vec4(1, 1, 1, 1);
	specular =	vec4(1, 1, 1, 1);
}

Light::Light(float x,float y,float z) {position = vec4(x, y, z, 1);}

void Light::setPosition(vec3 pos) {position = vec4(pos, 1);}
void Light::setAmbient(vec4 amb) {ambient = amb;}
void Light::setDiffuse(vec4 dif) {diffuse = dif;}
void Light::setSpecular(vec4 spec) {specular = spec;}


void Light::apply(GLenum LightNumber=GL_LIGHT0) {
	glEnable(LightNumber);
	GLfloat AMBIENT[4] = { ambient.r, ambient.g, ambient.b, ambient.a };
	GLfloat DIFFUSE[4] = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
	GLfloat SPECULAR[4] = { specular.r, specular.g, specular.b, specular.a };
	GLfloat POSITION[4] = { position.x, position.y, position.z, position.w };

	glLightfv(LightNumber, GL_AMBIENT, AMBIENT);
	glLightfv(LightNumber, GL_DIFFUSE, DIFFUSE);
	glLightfv(LightNumber, GL_SPECULAR, SPECULAR);
	glLightfv(LightNumber, GL_POSITION, POSITION);

}