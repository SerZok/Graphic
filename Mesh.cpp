#include "Mesh.h"

Mesh::Mesh(){}

//show vertex info (coord/tex.coord/normal)
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
	// вектор дл€ хранени€ геометрических координат
	std::vector<vec3> v;
	// вектор дл€ хранени€ нормалей
	std::vector<vec3> n;
	// вектор дл€ хранени€ текстурных координат
	std::vector<vec2> t;
	// вектор дл€ хранени€ индексов атрибутов, дл€ построени€ вершин
	//std::vector<ivec3> fPoints;

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

				for (int i = 0; i < 3; i++) {//„итаем 3 тройки
					if (i == 0) {	//ƒл€ первой тройки т.к. читаетс€ f
						iss >> key >> num11 >> sl >> num12 >> sl >> num13;
						keyV = to_string(num11) + "/" + to_string(num12) + "/" + to_string(num13);

						it = vertexToIndexTable.find(keyV);
						if (it != vertexToIndexTable.end()) {	//≈сли найден дубликат
							indexes.push_back(it->second);
						}
						else {
							//≈сли не нашли, то
							//«аписываем новый индекс в массив индексов,
							//—оздаем вершину
							//«аписываем в массив вершин
							index++;
							indexes.push_back(index);
							vertexToIndexTable.insert(pair<string, int>(keyV, index));
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
					else {	//дл€ 2 и 3 тройки
						iss >> num11 >> sl >> num12 >> sl >> num13;
						keyV = to_string(num11) + "/" + to_string(num12) + "/" + to_string(num13);

						it = vertexToIndexTable.find(keyV);
						if (it != vertexToIndexTable.end()) {	//≈сли найден дубликат
							indexes.push_back(it->second);
						}
						else {
							index++;
							indexes.push_back(index);
							vertexToIndexTable.insert(pair<string, int>(keyV, index));
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
	
				//fPoints.push_back(ivec3(num11, num12, num13));
				//fPoints.push_back(ivec3(num21, num22, num23));
				//fPoints.push_back(ivec3(num31, num32, num33));
			}
		}
		ifile.close();
		for (int i = 0; i < indexes.size(); i++) {
			cout << indexes[i] <<endl;
		}
		//Show();

		
		/*for (auto it = vertexToIndexTable.begin(); it != vertexToIndexTable.end(); it++) {
			istringstream isst(it->first);
			int n1, n2, n3;
			char cd;
			isst >> n1 >> cd >> n2 >> cd >> n3;

		}*/
		//for (int i = 0; i < fPoints.size(); i++) { //все вершин fPoints.size() дл€ fPoints.size()/3 полигонов
		//	for (int j =0; j < 3; j++) { //индексы дл€ вершин (координаты, нормали, координаты текстур)
		//		vert.coord[0] = v[fPoints[i].x - 1].x;
		//		vert.coord[1] = v[fPoints[i].x - 1].y;
		//		vert.coord[2] = v[fPoints[i].x - 1].z;
		//		vert.texCoord[0] = t[fPoints[i].y - 1].x;
		//		vert.texCoord[1] = t[fPoints[i].y - 1].y;
		//		vert.normal[0] = n[fPoints[i].z - 1].x;
		//		vert.normal[1] = n[fPoints[i].z - 1].y;
		//		vert.normal[2] = n[fPoints[i].z - 1].z;
		//	}
		//	vertices.push_back(vert);
		//}

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

	//glDrawArrays		(GL_TRIANGLES,0,vertices.size());
	glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, &indexes[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}