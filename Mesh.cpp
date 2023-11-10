#include "Mesh.h"

Mesh::Mesh(){}

void Mesh::Show() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << "Vertex: #" << i << endl;
		cout <<"Coord: "<< vertices[i].coord[0] << ' ' << vertices[i].coord[1] << ' ' << vertices[i].coord[2] << endl;
		cout <<"Normal: "<< vertices[i].normal[0] << ' ' << vertices[i].normal[1] << ' ' << vertices[i].normal[2]<< endl;
		cout <<"Texture: "<< vertices[i].texCoord[0] << ' ' << vertices[i].texCoord[1] << endl << endl;
	}
}

void Mesh::load(std::string filename) {
	// вектор для хранения геометрических координат
	std::vector<vec3> v;
	// вектор для хранения нормалей
	std::vector<vec3> n;
	// вектор для хранения текстурных координат
	std::vector<vec2> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	std::vector<ivec3> fPoints;

	ifstream ifile;
	ifile.open(filename);

	if (ifile.is_open()) {
		Vertex vert;
		string key;
		GLfloat x, y, z;
		int num11, num12, num13, num21, num22, num23, num31, num32, num33;

		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			istringstream ss(s);
			ss >> key >> x >> y >> z;
			char slash;

			if (key == "v")
				v.push_back(vec3(x, y, z));

			else if (key == "vn")
				n.push_back(vec3(x, y, z));

			else if (key == "vt")
				t.push_back(vec2(x, y));

			else if (key == "f") {
				istringstream iss(s);
				iss >> key >> num11 >> slash >> num12 >> slash >> num13;
				iss >> num21 >> slash >> num22 >> slash >> num23;
				iss >> num31 >> slash >> num32 >> slash >> num33;

				fPoints.push_back(ivec3(num11, num12, num13));
				fPoints.push_back(ivec3(num21, num22, num23));
				fPoints.push_back(ivec3(num31, num32, num33));
			}
			
		}
		ifile.close();
		for (int i = 0; i < fPoints.size(); i++) { //все вершин fPoints.size() для fPoints.size()/3 полигонов
			for (int j =0; j < 3; j++) { //индексы для вершин (координаты, нормали, координаты текстур)
				if (j == 0) {
					vert.coord[0] = v[fPoints[i].x - 1].x;
					vert.coord[1] = v[fPoints[i].x - 1].y;
					vert.coord[2] = v[fPoints[i].x - 1].z;
				}
				else if (j == 1) {
					vert.normal[0] = n[fPoints[i].y - 1].x;
					vert.normal[1] = n[fPoints[i].y - 1].y;
					vert.normal[2] = n[fPoints[i].y - 1].z;
				}
				else{
					vert.texCoord[0] = t[fPoints[i].z - 1].x;
					vert.texCoord[1] = t[fPoints[i].z - 1].y;
				}
			}
			vertices.push_back(vert);
		}

	}
	else {
		cout << "Error: can't open file! (meshes)" << endl;
		exit(-3);
	}

}

void Mesh::draw() {
	glEnableClientState( GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//первая координата первой вершины в массиве
	GLfloat* x = &vertices[0].coord[0];
	//Указатель на первое нормальное значение в массиве.
	GLfloat* n = &vertices[0].normal[0];
	//Указатель на первую координату первого элемента в массиве.
	GLfloat* t = &vertices[0].texCoord[0];
	
	glVertexPointer	(3, GL_FLOAT, 0, x);
	glNormalPointer	(GL_FLOAT, 0, n);
	glTexCoordPointer(2, GL_FLOAT, 0, t);
	glDrawArrays(GL_TRIANGLES,0,vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}