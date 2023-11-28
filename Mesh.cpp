#include "Mesh.h"

Mesh::Mesh(){}

void Mesh::load(std::string filename) {

	//массив вершин
	std::vector<Vertex>vertices;
	std::vector<GLuint>indexes;

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

	glGenBuffers(1, &bufferIds[0]);// Создать буфер
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);//Сделать буфер текущим
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);//Передать данные

	glGenBuffers(1, &bufferIds[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

	indexCount = indexes.size();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]); //Выбираем буфер
	glVertexPointer		(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glNormalPointer		(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glTexCoordPointer	(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, indexes.data());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}