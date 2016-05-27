#pragma once

#include <iostream>
#include <cmath>

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


struct Vertex {
	vec3 Position;
	//vec3 Normal;
	vec2 TexCoords;
};

class Mesh {
public:
	
	vec3 baseColor;
	vector<Vertex> vertices;
	vector<GLuint> textures;
	GLuint textureID;
	
	Mesh(string objName, vector<Vertex> vertices);
	void Draw(vec3 wPosition,Shader * shader);

private:
	GLuint VAO, VBO;
	void generateTexture();
	void setupMesh(string objName);
};