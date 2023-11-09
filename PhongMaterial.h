#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace glm;

class PhongMaterial{
private:
	vec4 ambient;	// фонова€ составл€юща€
	vec4 diffuse;	// диффузна€ составл€юща€
	vec4 specular;	// зеркальна€ составл€юща€
	vec4 emission;	// самосвечение
	float shininess;// степень отполированности
public:
	PhongMaterial();
	void setAmbient(vec4);
	void setDiffuse(vec4);
	void setSpecular(vec4);
	void setEmission(vec4);
	void setShininess(float );
	void load(std::string filename);
<<<<<<< HEAD
	void apply(void);

	void Show() {
		cout << this << endl;
		cout << ambient.r << ' ' << ambient.g << ' ' << ambient.b << ' ' << ambient.a<<endl;
		cout << diffuse.r << ' ' << diffuse.g << ' ' << diffuse.b << ' ' << diffuse.a<<endl;
		cout << specular.r << ' ' << specular.g << ' ' << specular.b << ' ' << specular.a<<endl;
		cout << emission.r << ' ' << emission.g << ' ' << emission.b << ' ' << emission.a << endl;
	}
	~PhongMaterial() {
		cout << "Distructor material" << endl;
	}
};
=======
	void apply();

	void Show(){
		cout << "\nMaterial: "<<this << endl;
		cout << "ambient :" << ambient.r << ' ' << ambient.g << ' ' << ambient.b << ' ' << ambient.a << endl;
		cout << "diffuse :" << diffuse.r << ' ' << diffuse.g << ' ' << diffuse.b << ' ' << diffuse.a << endl;
		cout << "specular :" << specular.r << ' ' << specular.g << ' ' << specular.b << ' ' << specular.a << endl;
		cout << "emission :" << emission.r << ' ' << emission.g << ' ' << emission.b << ' ' << emission.a << endl;
		cout << "shiness :" << shininess << endl;
	}
};
>>>>>>> 92be44369172a7bb7108788e4360bef0f3d66760
