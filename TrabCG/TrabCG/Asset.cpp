#include "Asset.h"

Asset::Asset()
{
}


Asset::~Asset()
{
}

void Asset::SetMesh(const std::string& meshPath)
{
	this->m_mesh = new Mesh(meshPath);
}

void Asset::SetShader(Shader* shader)
{
	this->m_shader = shader;
}

void Asset::SetPos(glm::vec3 pos)
{
	this->m_transform.SetPos(pos);
}

void Asset::SetRot(glm::vec3 rot)
{
	this->m_transform.SetRot(rot);
}

void Asset::SetScale(glm::vec3 scale)
{
	this->m_transform.SetScale(scale);
}

void Asset::SetMaterial(Material& material)
{
	this->m_material = &material;
}

void Asset::SetMaterial(std::vector<Material>& MaterialList)
{
	this->m_material = &MaterialList[this->id];
}

void Asset::Draw(const Camera& camera)
{
	//this->m_shader->Bind();

	//Bind material
	this->m_material->diffuse->Bind(0, m_shader);
	this->m_material->specular->Bind(1, m_shader);

	//glUniform1f(glGetUniformLocation(m_shader->Program(), "material.shininess"), m_material->shininess);

	this->m_shader->Update(m_transform, camera);
	this->m_mesh->Draw();

	//Unbind Material
	this->m_material->diffuse->Unbind();
	this->m_material->specular->Unbind();
}
