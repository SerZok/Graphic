#include "GameObjectFactory.h"

bool GameObjectFactory:: init(std::string filename) {
	
	ifstream f(filename);
	string jsonString;
	if (f.is_open()) {
		getline(f, jsonString, static_cast<char>(0));
	}
	else{
		cout << "Не уадется найти файл " << filename << endl;
		return false;
	}
	f.close();

	cout << "JSON string: " << jsonString<<endl;


	//shared_ptr <PhongMaterial> pmat1, pmat2, pmat3, pmat4, pmat5;
	//pmat1 = make_shared <PhongMaterial>();
	//pmat2 = make_shared <PhongMaterial>();
	//pmat3 = make_shared <PhongMaterial>();
	//pmat4 = make_shared <PhongMaterial>();
	//pmat5 = make_shared <PhongMaterial>();
	//pmat1->load("data//Materials//Border.txt");
	//pmat2->load("data//Materials//Box.txt");
	//pmat3->load("data//Materials//ChamferBox.txt");
	//pmat4->load("data//Materials//Plane.txt");
	//pmat5->load("data//Materials//Sphere.txt");
	//materials.push_back(pmat1);
	//materials.push_back(pmat2);
	//materials.push_back(pmat3);
	//materials.push_back(pmat4);
	//materials.push_back(pmat5);

	////Меши
	//shared_ptr <Mesh> mesh1, mesh2, mesh3, mesh4;
	//mesh1 = make_shared <Mesh>();
	//mesh2 = make_shared <Mesh>();
	//mesh3 = make_shared <Mesh>();
	//mesh4 = make_shared <Mesh>();
	//mesh1->load("data//Meshes//Box.obj");
	//mesh2->load("data//Meshes//ChamferBox.obj");
	//mesh3->load("data//Meshes//SimplePlane.obj");
	//mesh4->load("data//Meshes//Sphere.obj");
	//meshes.push_back(mesh1);
	//meshes.push_back(mesh2);
	//meshes.push_back(mesh3);
	//meshes.push_back(mesh4);

	//Object Box, ChamferBox, Sphere;

	//Box.set_mesh(meshes[0]);
	//ChamferBox.set_mesh(meshes[1]);
}

std::shared_ptr<GameObject> GameObjectFactory:: create(GameObjectType type, int x, int y) {
	shared_ptr<GameObject> obj;
	return obj;
}