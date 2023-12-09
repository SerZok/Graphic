#include <iostream>
#include <memory>
#include <fstream>	
#include "glew.h"
#include "rapidjson/document.h"


#include "GameObject.h"
#include "PhongMaterialWithTexture.h"
#include "PhongMaterial.h"

using namespace rapidjson;

// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum class GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект 0
	HEAVY_OBJECT, // тяжелый игровой объект 1
	BORDER_OBJECT, // граничный игровой объект 2
	PLAYER, // игровой объект для представления игрока 3
	BOMB, // игровой объект для представления бомбы 4
	MONSTER // игровой объект для представления монстров 5
};

class GameObjectFactory{
public:
	// инициализация фабрики (загрузка мешей и установка параметров материала)
	bool init(std::string filename);
	// создание нового объекта заданного типа
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	// меши для каждого типа объекта
	std::vector<std::shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	std::vector<std::shared_ptr<Material>> materials;
};