#include <iostream>
#include <memory>
#include <fstream>	
#include "glew.h"
#include "rapidjson/document.h"


#include "GameObject.h"
#include "PhongMaterialWithTexture.h"
#include "PhongMaterial.h"

using namespace rapidjson;

// ����������� ����� ������� ��������
enum class GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������ 0
	HEAVY_OBJECT, // ������� ������� ������ 1
	BORDER_OBJECT, // ��������� ������� ������ 2
	PLAYER, // ������� ������ ��� ������������� ������ 3
	BOMB, // ������� ������ ��� ������������� ����� 4
	MONSTER // ������� ������ ��� ������������� �������� 5
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
	std::vector<std::shared_ptr<Material>> materials;
};