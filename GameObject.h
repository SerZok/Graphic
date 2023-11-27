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
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(const Object& graphicObject);

	// ��������� ���������� ���������
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// ��������� ������� ���������� ���������
	ivec2 getPosition();

	void move(MoveDirection dir, float speed = 3.0f);
	const bool isMoving();
	void simulate(float sec);

	// ����� �������� ������� �� �����
	void draw();
private:
	MoveDirection sost;
	//�� 0 �� 1
	float progress;
	float speed;
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	Object graphicObject;
};