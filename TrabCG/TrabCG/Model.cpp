#include "Model.h"

Model::Model(GLchar* path)
{
	this->loadModel(path);
	this->LoadTexture("cube_diffuse.png");
}

Model::~Model()
{
}

void Model::Draw(Shader shader)
{
    for(GLuint i = 0; i < this->meshes.size(); i++)
        this->meshes[i].Draw(shader);
}  

void Model::loadModel(string path)
{
	ifstream inFile;
	inFile.open(path);

	//SET TEMPORARY VECTORS
	vector<vec3> temp_vertices;
	vector<vec2> temp_texCoords;
	vector<vec3> temp_verticeNormal;
	vector<GLuint> indices;
	vector<Vertex> final_vertices;

	GLchar input[32];

	while (!inFile.eof())
	{
		inFile >> input;
		
		if ((string)input == "v")
		{
			vec3 vertice;

			inFile >> input;
			vertice.x = stof(input);
			inFile >> input;
			vertice.y = stof(input);
			inFile >> input;
			vertice.z = stof(input);

			temp_vertices.push_back(vertice);
		}
		else if ((string)input == "vt")
		{
			vec2 texCoord;

			inFile >> input;
			texCoord.x = stof(input);
			inFile >> input;
			texCoord.y = stof(input);

			temp_texCoords.push_back(texCoord);
		}
		else if ((string)input == "vn")
		{
			vec3 verticeNormal;

			inFile >> input;
			verticeNormal.x = stof(input);
			inFile >> input;
			verticeNormal.y = stof(input);
			inFile >> input;
			verticeNormal.z = stof(input);

			temp_verticeNormal.push_back(verticeNormal);
		}
		else if ((string)input == "f")
		{
			while (true)
			{
				GLint verticeIndex, texCoordIndex, vertexNormalIndex;

				string auxString;

				Vertex vertice;

				inFile >> input;

				if ((string)input == "")
				{
					break;
				}
				else if ((string)input == "f")
				{
					inFile.unget();
					break;
				}

				auxString = (string)input;

				verticeIndex = stoi(auxString.substr(0, auxString.find_first_of('/'))) - 1;
				auxString = auxString.substr(auxString.find_first_of('/') + 1);
				texCoordIndex = stoi(auxString.substr(0, auxString.find_first_of('/'))) - 1;
				auxString = auxString.substr(auxString.find_first_of('/') + 1);
				vertexNormalIndex = stoi(auxString) - 1;

				vertice.Position = temp_vertices[verticeIndex];
				vertice.TexCoords = temp_texCoords[texCoordIndex];
				vertice.Normal = temp_verticeNormal[vertexNormalIndex];

				final_vertices.push_back(vertice);
			}
		}
	}

	this->directory = path.substr(0, path.find_last_of('/'));

	vector<Texture> textures;
	this->meshes.push_back(Mesh(final_vertices, textures));
}

void Model::LoadTexture(const GLchar* path)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	this->meshes[0].textureList.push_back(texture);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Model::LoadTextures(const char* path)
{
	// Load and create a texture 
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	Texture t;
	t.id = this->meshes[0].textures.size();
	string p = (string)path;
	//p = p.substr(p.find_last_of('/'));
	p = p.substr(0, p.find_last_of('.'));
	t.type = "texture_"+p;

	this->meshes[0].textures.push_back(t);
}