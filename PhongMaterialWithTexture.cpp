#include "PhongMaterialWithTexture.h"

PhongMaterialWithTexture::PhongMaterialWithTexture() {
	ambient = vec4(0, 0, 0, 1);
	diffuse = vec4(0, 0, 0, 1);
	specular = vec4(0, 0, 0, 1);
	emission = vec4(0, 0, 0, 1);
	shininess = 32;
}

void PhongMaterialWithTexture::setAmbient(vec4 amb) { ambient = amb; }
void PhongMaterialWithTexture::setDiffuse(vec4 diff) { diffuse = diff; }
void PhongMaterialWithTexture::setSpecular(vec4 spec) { specular = spec; }
void PhongMaterialWithTexture::setEmission(vec4 emiss) { emission = emiss; }
void PhongMaterialWithTexture::setShininess(float sh) { shininess = sh; }
void PhongMaterialWithTexture:: setTexture(std::shared_ptr<Texture> _texture){texture = _texture;}

void PhongMaterialWithTexture::load(std::string filename) {
	ifstream ifile;
	ifile.open(filename);

	float r, g, b, a;
	string key;

	if (ifile.is_open()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			istringstream ss(s);
			ss >> key >> r >> g >> b >> a;
			if (key == "ambient:")			ambient = (vec4(r, g, b, a));
			else if (key == "diffuse:")		diffuse = (vec4(r, g, b, a));
			else if (key == "specular:")	specular = (vec4(r, g, b, a));
			else if (key == "emission:")	emission = (vec4(r, g, b, a));
			else if (key == "shininess:")	shininess = (r);
		}
		ifile.close();
	}
	else {
		cout << "Error: can't open file! (material)" << endl;
		exit(-2);
	}
}

void PhongMaterialWithTexture::apply() {
	GLfloat AMBIENT[4] = { ambient.r, ambient.g, ambient.b, ambient.a };
	GLfloat DIFFUSE[4] = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
	GLfloat SPECULAR[4] = { specular.r, specular.g, specular.b, specular.a };
	GLfloat EMISSION[4] = { emission.r, emission.g, emission.b, emission.a };
	GLfloat SHININESS = shininess;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EMISSION);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SHININESS);

	if (texture != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		texture->apply();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

}
