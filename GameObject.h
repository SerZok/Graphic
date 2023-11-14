#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

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

	// вывод игрового объекта на экран
	void draw();
private:
	// логические координаты игрового объекта
	ivec2 position;
	// графический объект (для вывода на экран)
	Object graphicObject;
};