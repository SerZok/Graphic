#include "GameObject.h"

GameObject::GameObject() {

}

void GameObject::setGraphicObject(const Object& graphicObject) {this->graphicObject = graphicObject;}
void GameObject::setPosition(int x, int y) {position = ivec2(x, y);}
void GameObject::setPosition(ivec2 pos) {position = pos;}
ivec2 GameObject::getPosition() {return position;}

void GameObject::draw() {

}