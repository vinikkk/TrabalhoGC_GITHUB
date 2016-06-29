#include "Manager.h"



Manager::Manager()
{
	this->resourcePath = "../res/";

	//Set Default Material
	this->defaultMtl.SetDiffuse("../res/box.jpg");
	this->defaultMtl.SetSpecular("../res/box.jpg");
}


Manager::~Manager()
{
}

//Create an object
void Manager::CreateObject(std::string meshPath, std::string diffPath, std::string specPath, Shader* shader)
{
	Asset tempAsset;

	tempAsset.id = ObjectList.size();

	//Set Mesh
	tempAsset.SetMesh(meshPath);

	//Set Shader
	tempAsset.SetShader(shader);

	//Set Material
	//Material tempMaterial;
	this->MaterialList.resize(this->MaterialList.size() + 1);

	this->MaterialList[this->MaterialList.size() - 1].SetDiffuse(diffPath);
	this->MaterialList[this->MaterialList.size() - 1].SetSpecular(specPath);

	tempAsset.SetMaterial(this->MaterialList[this->MaterialList.size() - 1]);

	this->ObjectList.push_back(tempAsset);
}

void Manager::DrawObjects(const Camera& camera)
{
	for each (Asset object in this->ObjectList)
	{
		object.Draw(camera);
	}
}
