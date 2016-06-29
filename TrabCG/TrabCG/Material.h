#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"

class Material
{
public:
	Texture* diffuse;
	Texture* specular;
	float shininess;

	inline void SetDiffuse(const std::string texturePath) { this->diffuse = new Texture(texturePath); };
	inline void SetSpecular(const std::string texturePath) { this->specular = new Texture(texturePath); };
	inline void SetShininess(float value) { this->shininess = value; };

	Material() {};
	~Material() {};
};
#endif