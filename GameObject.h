#include <iostream>
#include <windows.h>
#include "glew.h"

#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

class GameObject {
public:
	GameObject();
	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(const Object& graphicObject);

	// установка логических координат
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// получение текущих логических координат
	ivec2 getPosition();

	void move(MoveDirection dir, float speed = 3.0f);
	const bool isMoving();
	void simulate(float sec);

	// вывод игрового объекта на экран
	void draw();
private:
	MoveDirection sost;
	//от 0 до 1
	float progress;
	float speed;
	// логические координаты игрового объекта
	ivec2 position;
	// графический объект (для вывода на экран)
	Object graphicObject;
};