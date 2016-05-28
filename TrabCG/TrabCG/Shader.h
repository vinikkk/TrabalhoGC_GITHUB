#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADER = 2;
	Shader(const Shader& other) {};
	void operator=(const Shader& other) {};

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif //SHADER_H

