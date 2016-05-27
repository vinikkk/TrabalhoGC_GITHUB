#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

//MY INCLUDES
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>

using namespace std;
using namespace glm;

class Object
{
public:
	
	//DATA
	string objectName;
	vec3 baseColor;
	vec3 worldPosition;
	vector<Mesh> meshList;
	vector<GLuint> textures;
	Shader *shader;

	Object(GLchar* path);
	~Object();

	void Draw();

	void setShader(Shader *shader) { this->shader = shader; };
	void setWorldPosition(vec3 wP) { this->worldPosition = wP; };
	void setBaseColor(vec3 bColor) { this->baseColor = bColor; };

protected:
	string directory;

	void loadMeshes(string path);
};

