/*
OBJLoader for the class of Computer Graphics at Unisinos 2016/1
Prof.: Rafael Hocevar
Author: Vinícius Pereira

TODO: Multiple OBJ sub Meshs
*/

#ifndef OBJ_LOADER_H_INCLUDED
#define OBJ_LOADER_H_INCLUDED

#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <string>

struct OBJIndex
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; };
};

struct Group
{
	std::string name;
	GLint id;

	std::vector<OBJIndex> OBJIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool hasUVs;
	bool hasNormals;
};

class IndexedModel
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	bool hasUVs;
	bool hasNormals;

	static const unsigned int NUM_BUFFERS = 4;
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;

	void CalcNormals();
};

class OBJModel
{
public:	
	std::vector<Group> GroupList;
	std::vector<IndexedModel> IndexedModelList;

	OBJModel(const std::string& fileName);

	std::vector<IndexedModel> ToIndexedModel();
private:
	unsigned int FindLastVertexIndex(Group group, const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
	void CreateOBJFace(const std::string& line);

	glm::vec2 ParseOBJVec2(const std::string& line);
	glm::vec3 ParseOBJVec3(const std::string& line);
	OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);

};

#endif