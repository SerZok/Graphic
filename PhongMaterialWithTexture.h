#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Material.h"

using namespace glm;
using namespace std;

class PhongMaterialWithTexture:public Material {
public:
	PhongMaterialWithTexture();
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);

	// установка используемой текстуры
	void setTexture(std::shared_ptr<Texture> _texture);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая
	vec4 ambient;
	// диффузная составялющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
	// используемая текстура
	std::shared_ptr<Texture> texture;
};