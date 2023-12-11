#include "Decal.h"


Decal::Decal() {
	position = ivec2(0, 0);
}
Decal::Decal(ivec2 position_) {
	position = position_;
}

// установка и получение логических координат
void Decal:: setPosition(ivec2 position_) {position = position_;}
ivec2 Decal::getPosition() {return position;}

void Decal::init() {
	Decal::material = std::make_shared<PhongMaterialWithTexture>();
	Decal::mesh = std::make_shared<Mesh>();

	std::shared_ptr<Texture> tDec = std::make_shared<Texture>();
	tDec->load("data\\Textures\\decal.png");
	material->load("data\\Materials\\DecalMaterial.txt");
	material->setTexture(tDec);
	mesh->load("data\\Meshes\\Decal.obj");
}

// вывод декали
void Decal::draw() {
	graphicObject.set_material(Decal::material);
	graphicObject.set_mesh(Decal::mesh);
	graphicObject.set_position(vec3(position.x - 10, 0  , position.y-10));
	graphicObject.draw();
}