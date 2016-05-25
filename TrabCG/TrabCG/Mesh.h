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
    vec3 Normal;
    vec2 TexCoords;
};

struct Texture {
    GLuint id;
    string type;
}; 

class Mesh {
    public:
        /*  Mesh Data  */
        vector<Vertex> vertices;
        vector<Texture> textures;
		vector<GLuint> textureList;
        /*  Functions  */
        Mesh(vector<Vertex> _vertices, vector<Texture> _textures);
        void Draw(Shader shader);
    private:
        /*  Render data  */
        GLuint VAO, VBO;
        /*  Functions    */
        void setupMesh();
}; 
