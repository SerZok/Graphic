#include <iostream>
#include <windows.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <fstream>
#include <string>
#include <sstream>
#include <map>

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
	//массив вершин
	std::vector<Vertex>vertices;
	std::vector<GLuint>indexes;
};
