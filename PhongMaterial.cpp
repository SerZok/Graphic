#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() {
	ambient = vec4(0, 0, 0, 1);
	diffuse = vec4(0, 0, 0, 1);
	specular = vec4(0, 0, 0, 1);
	emission = vec4(0, 0, 0, 1);
	shininess = 32;
}

void PhongMaterial::setAmbient(vec4 amb)	{ambient = amb;}
void PhongMaterial::setDiffuse(vec4 diff)	{diffuse = diff;}
void PhongMaterial::setSpecular(vec4 spec)	{specular = spec;}
void PhongMaterial::setEmission(vec4 emiss) {emission = emiss;}
void PhongMaterial::setShininess(float sh)	{shininess = sh;}

void PhongMaterial::load(std::string filename) {
	string path(filename);
	ifstream ifile;
	ifile.open(filename);
	if (ifile.is_open()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			cout << s;
		}
		ifile.close();
	}
	else {
		cout << "Error: can't open file! (ifstrem)" << endl;
		exit(-2);
	}
}

void PhongMaterial::apply() {
	GLfloat AMBIENT[4] = { ambient.r, ambient.g, ambient.b, ambient.a };
	GLfloat DIFFUSE[4] = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
	GLfloat SPECULAR[4] = { specular.r, specular.g, specular.b, specular.a };
	GLfloat EMISSION[4] = { emission.r, emission.g, emission.b, emission.a };
	GLfloat SHININESS = shininess;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EMISSION);
	glMaterialf	(GL_FRONT_AND_BACK, GL_SHININESS, SHININESS);

}
