#include <iostream>
#include <memory>
#include "GameObject.h"

#include "rapidjson/document.h"
#include <fstream>	

using namespace rapidjson;

// ����������� ����� ������� ��������
enum class GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	BOMB, // ������� ������ ��� ������������� �����
	MONSTER // ������� ������ ��� ������������� ��������
};

class GameObjectFactory{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	bool init(std::string filename);
	// �������� ������ ������� ��������� ����
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	// ���� ��� ������� ���� �������
	std::vector<std::shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	std::vector<std::shared_ptr<PhongMaterial>> materials;
};