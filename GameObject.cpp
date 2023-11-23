#include "GameObject.h"

GameObject::GameObject() {
	position.x = 0;
	position.y = 0;
	graphicObject.set_position(vec3(-10,0,-10));
}

void GameObject::setGraphicObject(const Object& graphicObject) {this->graphicObject = graphicObject;}

void GameObject::setPosition(int x, int y) {
	position = ivec2(x, y);
	graphicObject.set_position(vec3(x-10,0.51,y-10));
}

void GameObject::setPosition(ivec2 pos) {
	position = pos;
	graphicObject.set_position(vec3(pos.x - 10, 0.51, pos.y - 10));
}

ivec2 GameObject::getPosition() { return position; }
void GameObject::draw() { graphicObject.draw(); }