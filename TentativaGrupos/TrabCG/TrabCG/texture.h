#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {};
	void operator=(const Texture& texture) {};

	GLuint m_texture;
};

#endif //TEXTURE_H