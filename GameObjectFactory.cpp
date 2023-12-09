#include "GameObjectFactory.h"

#ifdef _MSC_VER
#undef GetObject
#endif


bool GameObjectFactory:: init(std::string filename) {
	ifstream f(filename);
	string jsonString;
	if (!f) return false;
	getline(f, jsonString, static_cast<char>(0));
	f.close();
	Document document;
	document.Parse(jsonString.c_str());

	if (document.GetParseError() != 0) {
		cout << "неверный формат файла\n";
		return false;
	}

	//m-объект
	for (auto& m : document.GetObject()) {
		string MeshFileName = document[m.name.GetString()]["mesh"].GetString();
		meshes.push_back(make_shared<Mesh>());
		meshes[meshes.size() - 1]->load(MeshFileName);

		const Value& material = document[m.name.GetString()]["material"];
		vec4 dif, amb, spec, emis;
		float shin = material["shininess"].GetFloat();
		for (int i = 0; i < 4; i++) {
			dif[i] = material["diffuse"][i].GetFloat();
			amb[i] = material["ambient"][i].GetFloat();
			spec[i] = material["specular"][i].GetFloat();
			emis[i] = material["emission"][i].GetFloat();
		}
		
		string type = material["type"].GetString();
		if (type == "PhongMaterialWithTexture") {//с материалом
			string TexturePath = material["texture"].GetString();
			shared_ptr<PhongMaterialWithTexture>pMaterial = make_shared<PhongMaterialWithTexture>();
			shared_ptr<Texture> pTexture = make_shared<Texture>();
			pTexture->load(TexturePath);
			pMaterial->setTexture(pTexture);

			pMaterial->setAmbient(amb);
			pMaterial->setDiffuse(dif);
			pMaterial->setEmission(emis);
			pMaterial->setShininess(shin);
			pMaterial->setSpecular(spec);
			materials.push_back(pMaterial);
		}
		else {//без материала
			shared_ptr<PhongMaterial>pMaterial = make_shared<PhongMaterial>();
			pMaterial->setAmbient(amb);
			pMaterial->setDiffuse(dif);
			pMaterial->setEmission(emis);
			pMaterial->setShininess(shin);
			pMaterial->setSpecular(spec);
			materials.push_back(pMaterial);
		}
	}
}

std::shared_ptr<GameObject> GameObjectFactory:: create(GameObjectType type, int x, int y) {
	shared_ptr<GameObject> GameObjP=make_shared<GameObject>();
	switch (type){
	case GameObjectType::LIGHT_OBJECT: {
		Object obj;
		obj.set_material(materials[0]);
		obj.set_mesh(meshes[0]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	case GameObjectType::HEAVY_OBJECT: {
		Object obj;
		obj.set_material(materials[1]);
		obj.set_mesh(meshes[1]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	case GameObjectType::BORDER_OBJECT: {
		Object obj;
		obj.set_material(materials[2]);
		obj.set_mesh(meshes[2]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	case GameObjectType::PLAYER: {
		Object obj;
		obj.set_material(materials[3]);
		obj.set_mesh(meshes[3]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	case GameObjectType::BOMB: {
		Object obj;
		obj.set_material(materials[4]);
		obj.set_mesh(meshes[4]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	case GameObjectType::MONSTER: {
		Object obj;
		obj.set_material(materials[5]);
		obj.set_mesh(meshes[5]);
		GameObjP->setGraphicObject(obj);
		GameObjP->setPosition(x, y);
		break;
	}
	default:
		break;
	}

	return GameObjP;
}