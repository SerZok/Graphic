#include "GameObject.h"

GameObject::GameObject() {
	speed = 0.01;
	position.x = 0;
	position.y = 0;
	graphicObject.set_position(vec3(-10,0,-10));
	sost = MoveDirection::STOP;
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
ivec2 GameObject::getPosition() {
	return position;
}

void GameObject::draw() {
	graphicObject.draw();
}

const bool GameObject::isMoving() {
	if (sost == MoveDirection::STOP)
		return false;
	return true;
}

void GameObject:: move(MoveDirection dir, float speed_){
	speed = speed_;
	sost = dir;
	progress = 0;
	if (sost!= MoveDirection::STOP) {
		switch (dir){
		case MoveDirection::LEFT: {
			position.x -= 1;
			break;
		}
		case MoveDirection::RIGHT: {
			position.x += 1;
			break;
		}
		case MoveDirection::UP: {
			position.y -= 1;
			break;
		}
		case MoveDirection::DOWN: {
			position.y += 1;
			break;
		}
		default:
			break;
		}
	}
}

void GameObject::simulate(float sec) {
	float dist = speed * sec;
	progress+=dist;
	vec3 currentPos = graphicObject.get_position();
	if (progress < 1) {
		switch (sost) {
		case MoveDirection::LEFT: {
			currentPos.x -= dist;
			break;
		}
		case MoveDirection::RIGHT: {
			currentPos.x += dist;
			break;
		}
		case MoveDirection::UP: {
			currentPos.z -= dist;
			break;
		}
		case MoveDirection::DOWN: {
			currentPos.z += dist;
			break;
		}
		case MoveDirection::STOP:
			break;

		default:
			break;
		}
	}
	else {//Если закончил движение
		sost = MoveDirection::STOP;
		progress = 1.0f;
		currentPos = vec3(position.x - 10, 0.5, position.y - 10);
	}
	graphicObject.set_position(currentPos);
}