#ifndef TEXTURE_H
#define TEXTURE_H

#include "shader.h"
#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture() {};
	Texture(const std::string& fileName);
	//Texture();

	void Bind(unsigned int unit);
	void Bind(unsigned int unit, Shader* shader);

	void Unbind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {};
	void operator=(const Texture& texture) {};

	GLuint m_texture;
	GLuint m_unit;
};

#endif //TEXTURE_H