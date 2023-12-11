#pragma once
#include "glm/glm.hpp"
#include "Object.h"
#include "PhongMaterialWithTexture.h"

using namespace glm;

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ДЕКАЛИ
class Decal{
public:
	// загрузка меша, загрузка текстуры и создание материала
	static void init();
	// конструкторы: по-умолчанию и с указание логических координат
	Decal();
	Decal(ivec2 position);
	// установка и получение логических координат
	void setPosition(ivec2 position);
	ivec2 getPosition();
	// вывод декали
	void draw();
private:
	// графический объект для представления декали
	Object graphicObject;
	// логическая позиция декали
	ivec2 position;
	// общий материал для всех декалей
	static std::shared_ptr<PhongMaterialWithTexture> material;
	// общий меш для всех декалей
	static std::shared_ptr <Mesh> mesh;
};

//std::shared_ptr<PhongMaterialWithTexture> Decal::material = std::make_shared<PhongMaterialWithTexture>();
//std::shared_ptr <Mesh> Decal::mesh = std::make_shared<Mesh>();