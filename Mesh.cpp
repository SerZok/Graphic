#include "Mesh.h"

Mesh::Mesh(){}

void Mesh::load(std::string filename) {
	// вектор для хранения геометрических координат
	std::vector<vec3> v;
	// вектор для хранения нормалей
	std::vector<vec3> n;
	// вектор для хранения текстурных координат
	std::vector<vec2> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	std::vector<ivec3> fPoints;

	Vertex vert;
	ifstream ifile;
	ifile.open(filename);

	string key;
	GLfloat x, y, z;
	int num11, num12, num13,num21,num22,num23,num31,num32,num33;

	if (ifile.is_open()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			istringstream ss(s);
			ss >> key >> x >> y >> z;
			char slash='/';

			if (key == "v")
				v.push_back(vec3(x, y, z));

			else if (key == "vn")
				n.push_back(vec3(x, y, z));

			else if (key == "vt")
				t.push_back(vec3(x, y, z));

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
		for (int i = 0; i < fPoints.size(); i++) { //все 36 вершин для 12 полигонов
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
					cout << t[i].x << endl;
				}
			}
			vertices.push_back(vert);
		}
		cout << vertices[0].coord[0] << ' ' << vertices[0].coord[1] << ' ' << vertices[0].coord[2] << endl;
		cout << vertices[0].normal[0] << ' ' << vertices[0].normal[1] << ' ' << vertices[0].normal[2] << endl << endl;

	}
	else {
		cout << "Error: can't open file! (meshes)" << endl;
		exit(-3);
	}

}