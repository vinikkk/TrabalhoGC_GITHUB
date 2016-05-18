#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Draw(Shader shader)
{
    for(GLuint i = 0; i < this->meshes.size(); i++)
        this->meshes[i].Draw(shader);
}  

void loadModel(string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    
    this->processNode(scene->mRootNode, scene);
}

void processNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        this->meshes.push_back(this->processMesh(mesh, scene));			
    }
    // Then do the same for each of its children
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }
} 

Mesh processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // Process vertex positions, normals and texture coordinates
        ...
        vertices.push_back(vertex);
    }
    // Process indices
    ...
    // Process material
    if(mesh->mMaterialIndex >= 0)
    {
        ...
    }

    return Mesh(vertices, indices, textures);
} 
