#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stddef.h>

#include <glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 


using namespace glm;
using namespace std;

struct Vertex {
	GLfloat coord[3];
	GLfloat normal[3];
	GLfloat texCoord[2];
};

class Mesh {
public:
	Mesh();
	//show vertex params
	void Show();
	void load(std::string);
	void draw();
private:

	int indexCount;
	//0-Вершины, 1-Индексы
	GLuint bufferIds[2];

};
