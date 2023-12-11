#pragma once
#include "glm/glm.hpp"
#include "Object.h"
#include "PhongMaterialWithTexture.h"

using namespace glm;

// ����� ��� ������������� ������
class Decal{
public:
	// �������� ����, �������� �������� � �������� ���������
	static void init();
	// ������������: ��-��������� � � �������� ���������� ���������
	Decal();
	Decal(ivec2 position);
	// ��������� � ��������� ���������� ���������
	void setPosition(ivec2 position);
	ivec2 getPosition();
	// ����� ������
	void draw();
private:
	// ����������� ������ ��� ������������� ������
	Object graphicObject;
	// ���������� ������� ������
	ivec2 position;
	// ����� �������� ��� ���� �������
	static std::shared_ptr<PhongMaterialWithTexture> material;
	// ����� ��� ��� ���� �������
	static std::shared_ptr <Mesh> mesh;
};

//std::shared_ptr<PhongMaterialWithTexture> Decal::material = std::make_shared<PhongMaterialWithTexture>();
//std::shared_ptr <Mesh> Decal::mesh = std::make_shared<Mesh>();