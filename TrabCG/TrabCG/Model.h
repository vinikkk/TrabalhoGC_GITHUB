#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

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

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

using namespace std;

class Model
{
public:
	//DATA
	string objectId;
	//Shader shader;
	
	//FUNCTIONS
	Model(GLchar* path);
	~Model();
	void Draw(Shader shader);
	
private:
	string objectMeshPath;
	vector<Mesh> meshes;
	string directory;
    void loadModel(string path);

	void LoadTexture(const GLchar * path);

	void LoadTextures(const char* path);
};

