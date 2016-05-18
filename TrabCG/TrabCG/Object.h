#pragma once

#include <string>
#include "Mesh.h"
#include "Shader.h"

class Object
{
public:
	//DATA
	string objectId;
	Shader shader;
	
	//FUNCTIONS
	Object();
	~Object(GLchar* path) { this->loadModel(path); };
	void Draw();
	
private:
	vector<Mesh> meshes;
	string directory;
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

