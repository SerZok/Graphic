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
<<<<<<< HEAD
	ifile.open(filename);
=======
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760

	float r, g, b, a;
	string key;

<<<<<<< HEAD
=======
	ifile.open(path);
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
	if (ifile.is_open()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
  			istringstream ss(s);
			ss>> key >> r >> g >> b >> a;
			//cout << key<<' ' << r <<' '<< g<<' ' << b<<' ' << a << endl;
<<<<<<< HEAD

			if (key == "ambient:")			ambient=(vec4(r, g, b, a));
			else if (key == "diffuse:")		diffuse=(vec4(r, g, b, a));
			else if (key == "specular:")	specular=(vec4(r, g, b, a));
			else if (key == "emission:")	emission=(vec4(r, g, b, a));
			else if (key == "shininess:")	shininess= (r);
=======
			if		(key == "ambient:")		ambient=vec4(r, g, b, a);
			else if (key == "diffuse:")		diffuse=vec4(r, g, b, a);
			else if (key == "specular:")	specular=vec4(r, g, b, a);
			else if (key == "emission:")	emission=vec4(r, g, b, a);
			else if (key == "shininess:")	shininess=r;
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
		}
		ifile.close();
	}
	else {
		cout << "Error: can't open file! " << endl;
		exit(-2);
	}
}

void PhongMaterial::apply() {
<<<<<<< HEAD
	//Show();
=======
	//cout <<"\nTHIS: " << this:  << endl;
	//cout << "DIFFUSE :" << diffuse.r << ' ' << diffuse.g << ' ' << diffuse.b << ' ' << diffuse.a << endl<<endl;
	Show();
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760

	GLfloat AMBIENT[4] = { ambient.r, ambient.g, ambient.b, ambient.a };
	GLfloat DIFFUSE[4] = { diffuse.r, diffuse.g, diffuse.b, diffuse.a };
	GLfloat SPECULAR[4] ={ specular.r, specular.g, specular.b, specular.a };
	GLfloat EMISSION[4] ={ emission.r, emission.g, emission.b, emission.a };
	GLfloat SHININESS = shininess;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  AMBIENT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, EMISSION);
	glMaterialf	(GL_FRONT_AND_BACK, GL_SHININESS,SHININESS);
<<<<<<< HEAD

}
=======
}
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
