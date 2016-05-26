#include "Object.h"

Object::Object(GLchar* path)
{
	string s = (string)path;
	//s = s.substr(s.find_last_of('/'));
	this->objectName = s.substr(0, s.find_last_of('.'));

	this->worldPosition = vec3(0.0f);

	this->loadMeshes(path);
}


Object::~Object()
{
}

void Object::Draw()
{
	for each (Mesh m in meshList)
	{
		m.Draw(this->worldPosition, this->shader);
	}
}

void Object::loadMeshes(string path)
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

	this->meshList.push_back(Mesh(objectName, final_vertices));
}
