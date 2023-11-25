#include "Mesh.h"

Mesh::Mesh(){}

//show vertex info (№verterx/coord/tex.coord/normal)
void Mesh::Show() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << "Vertex: #" << i <<"\nID: "<<indexes[i] << endl;
		cout <<"Coord: "<< vertices[i].coord[0] << ' ' << vertices[i].coord[1] << ' ' << vertices[i].coord[2] << endl;
		cout << "Texture: " << vertices[i].texCoord[0] << ' ' << vertices[i].texCoord[1] << endl;
		cout <<"Normal: "<< vertices[i].normal[0] << ' ' << vertices[i].normal[1] << ' ' << vertices[i].normal[2]<< endl;
		cout << endl;
	}
	cout << "*************************************" << endl;
}

void Mesh::load(std::string filename) {
	// вектор для хранения геометрических координат
	std::vector<vec3> v;
	// вектор для хранения нормалей
	std::vector<vec3> n;
	// вектор для хранения текстурных координат
	std::vector<vec2> t;

	//example: key=(1/2/3) value(id vertex) =1
	int index=0;

	ifstream ifile;
	ifile.open(filename);

	if (ifile.is_open()) {
		Vertex vert;
		string key;
		string keyV;
		GLfloat x, y, z;
		int num11, num12, num13, num21, num22, num23, num31, num32, num33;
		map<string, int>vertexToIndexTable;
		map<string, int>::iterator it;

		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			istringstream ss(s);
			ss >> key >> x >> y >> z;
			char sl;

			if (key == "v")			v.push_back(vec3(x, y, z));
			else if (key == "vn")	n.push_back(vec3(x, y, z));
			else if (key == "vt")	t.push_back(vec2(x, y));
			else if (key == "f") {
				istringstream iss(s);

				for (int i = 0; i < 3; i++) {//Читаем 3 тройки
					if (i == 0) {			//Для первой тройки т.к. читается f
						iss >> key >> num11 >> sl >> num12 >> sl >> num13;
						keyV = to_string(num11) + "/" + to_string(num12) + "/" + to_string(num13);

						it = vertexToIndexTable.find(keyV);
						if (it != vertexToIndexTable.end()) {	//Если найден дубликат
							indexes.push_back(it->second);
						}
						else {
							//Если не нашли, то
							//Записываем новый индекс в массив индексов,
							//Создаем вершину
							//Записываем в массив вершин
							indexes.push_back(index);
							vertexToIndexTable.insert(pair<string, int>(keyV, index));
							index++;
							vert.coord[0] = v[num11 - 1].x;
							vert.coord[1] = v[num11 - 1].y;
							vert.coord[2] = v[num11 - 1].z;
							vert.texCoord[0] = t[num12 - 1].x;
							vert.texCoord[1] = t[num12 - 1].y;
							vert.normal[0] = n[num13 - 1].x;
							vert.normal[1] = n[num13 - 1].y;
							vert.normal[2] = n[num13 - 1].z;
							vertices.push_back(vert);
						}
					}
					else {	//для 2 и 3 тройки
						iss >> num11 >> sl >> num12 >> sl >> num13;
						keyV = to_string(num11) + "/" + to_string(num12) + "/" + to_string(num13);
						it = vertexToIndexTable.find(keyV);
						if (it != vertexToIndexTable.end()) {	//Если найден дубликат
							indexes.push_back(it->second);
						}
						else {
							indexes.push_back(index);
							vertexToIndexTable.insert(pair<string, int>(keyV, index));
							index++;
							vert.coord[0] = v[num11 - 1].x;
							vert.coord[1] = v[num11 - 1].y;
							vert.coord[2] = v[num11 - 1].z;
							vert.texCoord[0] = t[num12 - 1].x;
							vert.texCoord[1] = t[num12 - 1].y;
							vert.normal[0] = n[num13 - 1].x;
							vert.normal[1] = n[num13 - 1].y;
							vert.normal[2] = n[num13 - 1].z;
							vertices.push_back(vert);
						}
					}
				}
			}
		}
		ifile.close();
	}
	else {
		cout << "Error: can't open file! (meshes)" << endl;
		exit(-3);
	}

}

void Mesh::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer		(3, GL_FLOAT, sizeof(Vertex), &vertices[0].coord[0]);
	glNormalPointer		(GL_FLOAT, sizeof(Vertex), &vertices[0].normal[0]);
	glTexCoordPointer	(2, GL_FLOAT, sizeof(Vertex), &vertices[0].texCoord[0]);

	glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, indexes.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}