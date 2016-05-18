#pragma once

#include <string>
#include "Mesh.h"
#include "Shader.h"

class Model
{
public:
	//DATA
	string objectId;
	Shader shader;
	
	//FUNCTIONS
	Model();
	~Model(GLchar* path) { this->loadModel(path); };
	void Draw();
	
private:
	string objectMeshPath
	vector<Mesh> meshes;
	string directory;
        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

