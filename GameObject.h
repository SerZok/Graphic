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
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(const Object& graphicObject);

	// ��������� ���������� ���������
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// ��������� ������� ���������� ���������
	ivec2 getPosition();

	// ����� �������� ������� �� �����
	void draw();
private:
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	Object graphicObject;
};