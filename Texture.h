#include <iostream>
#include "glew.h"

#include "Il/il.h"
#include "Il/ilu.h"
#include "Il/ilut.h"
#include "GL/Glut.h"
#include <string>

// ������������ ��� ����������� ������ ����������
enum class TextureFilter {
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};

// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(std::string filename);

	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter  texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
};

