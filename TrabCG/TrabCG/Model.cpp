#include "Model.h"

Model::Model(GLchar* path)
{
	//this->loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader shader)
{
    //for(GLuint i = 0; i < this->meshes.size(); i++)
        //this->meshes[i].Draw(shader);
}  

void Model::loadModel(string path)
{
	ifstream inFile;
	inFile.open(path);

	//SET TEMPORARY VECTORS
	vector<Vertex> temp_vertices;
	vector<vec2> temp_texCoords;
	vector<vec3> temp_verticeNormal;

	GLchar input[32];
	GLchar line[256];

	while (!inFile.eof())
	{
		inFile.get(input, 32);
		
		if ((string)input == "#")
		{
			inFile.getline(line, 256);
		}
		else if ((string)input == "v")
		{

		}


	}


    //this->directory = path.substr(0, path.find_last_of('/'));
}

/*void Model::processNode(aiNode* node, const aiScene* scene)
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

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    /*vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // Process vertex positions, normals and texture coordinates
        //...
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
} */
