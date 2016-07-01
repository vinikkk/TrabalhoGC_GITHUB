#include "Manager.h"



Manager::Manager()
{
	this->resourcePath = "../res/";
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
	tempAsset.SetMaterial(diffPath, specPath);

	this->ObjectList.push_back(tempAsset);
}

void Manager::SetRandomMaterial(GLint index)
{
	switch (index)
	{
	case 0:
		ObjectList[currentAssetIndex].SetMaterial("noise0.bmp", "noise0.bmp");
		break;
	case 1:
		ObjectList[currentAssetIndex].SetMaterial("noise1.bmp", "noise1.bmp");
		break;
	case 2:
		ObjectList[currentAssetIndex].SetMaterial("noise2.bmp", "noise2.bmp");
		break;
	case 3:
		ObjectList[currentAssetIndex].SetMaterial("noise3.bmp", "noise3.bmp");
		break;
	case 4:
		ObjectList[currentAssetIndex].SetMaterial("noise4.bmp", "noise4.bmp");
		break;
	}
}

void Manager::DrawObjects(const Camera& camera)
{
	for each (Asset object in this->ObjectList)
	{
		object.Draw(camera);
	}
}
