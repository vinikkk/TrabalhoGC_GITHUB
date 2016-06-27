/*
OBJLoader for the class of Computer Graphics at Unisinos 2016/1
Prof.: Rafael Hocevar
Author: Vinícius Pereira

TODO: Texture Coordinates, Multiple OBJ sub Meshs
*/

#include "obj_loader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

static bool CompareOBJIndexPtr(const OBJIndex* a, const OBJIndex* b);
static inline unsigned int FindNextChar(unsigned int start, const char* str, unsigned int length, char token);
static inline unsigned int ParseOBJIndexValue(const std::string& token, unsigned int start, unsigned int end);
static inline float ParseOBJFloatValue(const std::string& token,  unsigned int start, unsigned int end);
static inline std::vector<std::string> SplitString(const std::string &s,  char delim);

void IndexedModel::CalcNormals()
{
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 v1 = positions[i1] - positions[i0];
		glm::vec3 v2 = positions[i2] - positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	for (unsigned int i = 0; i < positions.size(); i++)
		normals[i] = glm::normalize(normals[i]);
}

OBJModel::OBJModel(const std::string & fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string line;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			unsigned int lineLength = line.length();

			if (lineLength < 2)
				continue;

			const char* lineCStr = line.c_str();

			switch (lineCStr[0])
			{
			case 'g':
				if (line.substr(2) == "default")
				{
					Group newGroup;

					newGroup.id = GroupList.size();

					newGroup.hasUVs = false;
					newGroup.hasNormals = false;

					this->GroupList.push_back(newGroup);
				}
				else
				{
					this->GroupList.back().name = line.substr(2);
				}
				break;
			case 'v':

				if (GroupList.size() == 0)
				{
					Group newGroup;

					newGroup.name = fileName;
					newGroup.id = GroupList.size();

					newGroup.hasUVs = false;
					newGroup.hasNormals = false;

					this->GroupList.push_back(newGroup);
				}

				if (lineCStr[1] == 't')
					this->GroupList.back().uvs.push_back(ParseOBJVec2(line));
				else if (lineCStr[1] == 'n')
					this->GroupList.back().normals.push_back(ParseOBJVec3(line));
				else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
					this->GroupList.back().vertices.push_back(ParseOBJVec3(line));
			break;
			case 'f':
				CreateOBJFace(line);
			break;
			default: break;
			}
		}
	}
	else
	{
		std::cerr << "Unable to load mesh: " << fileName << std::endl;
	}
}

std::vector<IndexedModel> OBJModel::ToIndexedModel()
{
	GLint vertexPos = 0, uvPos = 0;

	for each (Group group in GroupList)
	{
		IndexedModel result;
		IndexedModel normalModel;

		unsigned int numIndices = group.OBJIndices.size();

		std::vector<OBJIndex*> indexLookup;

		for (unsigned int i = 0; i < numIndices; i++)
			indexLookup.push_back(&group.OBJIndices[i]);

		std::sort(indexLookup.begin(), indexLookup.end(), CompareOBJIndexPtr);

		std::map<OBJIndex, unsigned int> normalModelIndexMap;
		std::map<unsigned int, unsigned int> indexMap;

		vertexPos += (group.id > 0) ? GroupList[group.id - 1].vertices.size() : 0;
		uvPos += (group.id > 0) ? GroupList[group.id - 1].uvs.size() : 0;

		for (unsigned int i = 0; i < numIndices; i++)
		{
			OBJIndex* currentIndex = &group.OBJIndices[i];

			glm::vec3 currentPosition = group.vertices[currentIndex->vertexIndex - vertexPos];
			glm::vec2 currentTexCoord;
			glm::vec3 currentNormal;

			if (group.hasUVs)
				currentTexCoord = group.uvs[currentIndex->uvIndex - uvPos];
			else
				currentNormal = glm::vec3(0, 0, 0);

			unsigned int normalModelIndex;
			unsigned int resultModelIndex;

			std::map<OBJIndex, unsigned int>::iterator it = normalModelIndexMap.find(*currentIndex);
			if (it == normalModelIndexMap.end())
			{
				normalModelIndex = normalModel.positions.size();

				normalModelIndexMap.insert(std::pair<OBJIndex, unsigned int>(*currentIndex, normalModelIndex));
				normalModel.positions.push_back(currentPosition);
				normalModel.texCoords.push_back(currentTexCoord);
				normalModel.normals.push_back(currentNormal);
			}
			else
				normalModelIndex = it->second;

			unsigned int previousVertexLocation = FindLastVertexIndex(group, indexLookup, currentIndex, result);

			if (previousVertexLocation == (unsigned int)-1)
			{
				resultModelIndex = result.positions.size();

				result.positions.push_back(currentPosition);
				result.texCoords.push_back(currentTexCoord);
				result.normals.push_back(currentNormal);
			}
			else
				resultModelIndex = previousVertexLocation;

			normalModel.indices.push_back(normalModelIndex);
			result.indices.push_back(resultModelIndex);
			indexMap.insert(std::pair<unsigned int, unsigned int>(resultModelIndex, normalModelIndex));
		}

		if (!group.hasNormals)
		{
			normalModel.CalcNormals();

			for (unsigned int i = 0; i < result.positions.size(); i++)
			{
				result.normals[i] = normalModel.normals[indexMap[i]];
			}
		}

		result.hasUVs = group.hasUVs;
		result.hasNormals = group.hasNormals;

		IndexedModelList.push_back(result);
	}

	return IndexedModelList;
}

unsigned int OBJModel::FindLastVertexIndex(Group group, const std::vector<OBJIndex*>& indexLookup, const OBJIndex * currentIndex, const IndexedModel & result)
{
	unsigned int start = 0;
	unsigned int end = indexLookup.size();
	unsigned int current = (end - start) / 2 + start;
	unsigned int previous = start;

	while (current != previous)
	{
		OBJIndex* testIndex = indexLookup[current];

		if (testIndex->vertexIndex == currentIndex->vertexIndex)
		{
			unsigned int countStart = current;

			for (unsigned int i = 0; i < current; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current - i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;

				countStart--;
			}

			for (unsigned int i = countStart; i < indexLookup.size() - countStart; i++)
			{
				OBJIndex* possibleIndex = indexLookup[current + i];

				if (possibleIndex == currentIndex)
					continue;

				if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
					break;
				else if ((!group.hasUVs || possibleIndex->uvIndex == currentIndex->uvIndex)
					&& (!group.hasNormals || possibleIndex->normalIndex == currentIndex->normalIndex))
				{
					glm::vec3 currentPosition = group.vertices[currentIndex->vertexIndex];
					glm::vec2 currentTexCoord;
					glm::vec3 currentNormal;

					if (group.hasUVs)
						currentTexCoord = group.uvs[currentIndex->uvIndex];
					else
						currentTexCoord = glm::vec2(0, 0);

					if (group.hasNormals)
						currentNormal = group.normals[currentIndex->normalIndex];
					else
						currentNormal = glm::vec3(0, 0, 0);

					for (unsigned int j = 0; j < result.positions.size(); j++)
					{
						if (currentPosition == result.positions[j]
							&& ((!group.hasUVs || currentTexCoord == result.texCoords[j])
								&& (!group.hasNormals || currentNormal == result.normals[j])))
						{
							return j;
						}
					}
				}
			}

			return -1;
		}
		else
		{
			if (testIndex->vertexIndex < currentIndex->vertexIndex)
				start = current;
			else
				end = current;
		}

		previous = current;
		current = (end - start) / 2 + start;
	}

	return -1;
}

void OBJModel::CreateOBJFace(const std::string & line)
{
	std::vector<std::string> tokens = SplitString(line, ' ');

	this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));
	this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[2], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));
	this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));

	if ((int)tokens.size() > 4)
	{
		this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[1], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));
		this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[3], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));
		this->GroupList.back().OBJIndices.push_back(ParseOBJIndex(tokens[4], &this->GroupList.back().hasUVs, &this->GroupList.back().hasNormals));
	}
}

glm::vec2 OBJModel::ParseOBJVec2(const std::string & line)
{
	unsigned int tokenLength = line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 3;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return glm::vec2(x, y);
}

glm::vec3 OBJModel::ParseOBJVec3(const std::string & line)
{
	unsigned int tokenLength = line.length();
	const char* tokenString = line.c_str();

	unsigned int vertIndexStart = 2;

	while (vertIndexStart < tokenLength)
	{
		if (tokenString[vertIndexStart] != ' ')
			break;
		vertIndexStart++;
	}

	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float x = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float y = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, ' ');

	float z = ParseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

	return glm::vec3(x, y, z);
}

OBJIndex OBJModel::ParseOBJIndex(const std::string & token, bool * hasUVs, bool * hasNormals)
{
	unsigned int tokenLength = token.length();
	const char* tokenString = token.c_str();

	unsigned int vertIndexStart = 0;
	unsigned int vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	OBJIndex result;
	result.vertexIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	result.uvIndex = 0;
	result.normalIndex = 0;

	if (vertIndexEnd >= tokenLength)
		return result;

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	result.uvIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasUVs = true;

	if (vertIndexEnd >= tokenLength)
		return result;

	vertIndexStart = vertIndexEnd + 1;
	vertIndexEnd = FindNextChar(vertIndexStart, tokenString, tokenLength, '/');

	result.normalIndex = ParseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
	*hasNormals = true;

	return result;
}

bool CompareOBJIndexPtr(const OBJIndex * a, const OBJIndex * b)
{
	return a->vertexIndex < b->vertexIndex;
}

inline unsigned int FindNextChar(unsigned int start, const char * str, unsigned int length, char token)
{
	unsigned int result = start;
	while (result < length)
	{
		result++;
		if (str[result] == token)
			break;
	}

	return result;
}

inline unsigned int ParseOBJIndexValue(const std::string & token, unsigned int start, unsigned int end)
{
	return atoi(token.substr(start, end - start).c_str()) - 1;
}

inline float ParseOBJFloatValue(const std::string & token, unsigned int start, unsigned int end)
{
	return atof(token.substr(start, end - start).c_str());
}

inline std::vector<std::string> SplitString(const std::string & s, char delim)
{
	std::vector<std::string> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength)
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
			{
				break;
			}
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}
