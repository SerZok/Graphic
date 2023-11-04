#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() {
	ambient = vec4(0, 0, 0, 1);
	diffuse = vec4(0, 0, 0, 1);
	specular = vec4(0, 0, 0, 1);
	emission = vec4(0, 0, 0, 1);
	shininess = 32;
}

void PhongMaterial::setAmbient(vec4 amb) { ambient = amb; }
void PhongMaterial::setDiffuse(vec4 diff)	{diffuse = diff;}
void PhongMaterial::setSpecular(vec4 spec)	{specular = spec;}
void PhongMaterial::setEmission(vec4 emiss) {emission = emiss;}
void PhongMaterial::setShininess(float sh)	{shininess = sh;}

void PhongMaterial::load(std::string filename) {
	//string path(filename);
	ifstream ifile;
	ifile.open(filename);

	float r, g, b, a;
	string key;

	if (ifile.is_open()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
  			istringstream ss(s);
			ss>> key >> r >> g >> b >> a;
			//cout << key<<' ' << r <<' '<< g<<' ' << b<<' ' << a << endl;

			if (key == "ambient:")			ambient=(vec4(r, g, b, a));
			else if (key == "diffuse:")		diffuse=(vec4(r, g, b, a));
			else if (key == "specular:")	specular=(vec4(r, g, b, a));
			else if (key == "emission:")	emission=(vec4(r, g, b, a));
			else if (key == "shininess:")	shininess= (r);
		}
		ifile.close();
	}
	else {
		cout << "Error: can't open file! (ifstrem)" << endl;
		exit(-2);
	}
}

void PhongMaterial::apply(void) {
	GLfloat AMBIENT[4] = { 1, 0, 0, 1 };
	cout << "ambient PhongMaterial:" << ambient.r<<' ' << ambient.g<<' ' << ambient.b<<' ' << ambient.a << endl;

	GLfloat DIFFUSE[4] = { 1, 0, 0, 1 };
	GLfloat SPECULAR[4] = { specular.r, specular.g, specular.b, specular.a };
	GLfloat EMISSION[4] = { emission.r, emission.g, emission.b, emission.a };
	GLfloat SHININESS = shininess;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  AMBIENT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EMISSION);
	glMaterialf	(GL_FRONT_AND_BACK, GL_SHININESS,SHININESS);

}
