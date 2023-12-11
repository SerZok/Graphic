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
	material->load("data\\Material\\DecalMaterial.txt");
	std::shared_ptr<Texture> tDec = std::make_shared<Texture>();
	tDec->load("data\\Textures\\decal.png");
	mesh->load("data\\Meshes\\Decal.obj");
}

// вывод декали
void Decal::draw() {

}