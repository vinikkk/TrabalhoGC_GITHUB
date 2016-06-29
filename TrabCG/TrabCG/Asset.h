#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "Material.h"

class Asset
{
public:
	Asset();
	~Asset();

	GLuint id;

	void SetMesh(const std::string& meshPath);
	void SetShader(Shader* shader);

	//Transform Functions
	void SetPos(glm::vec3 pos);
	void SetRot(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	void SetMaterial(Material& material);
	void SetMaterial(std::vector<Material>& MaterialList);

	void Draw(const Camera& camera);

protected:
private:
	Mesh* m_mesh;
	Shader* m_shader;
	Material* m_material;
	Transform m_transform;
};

#endif