#ifndef TEXTUREGENERATOR_H
#define TEXTUREGENERATOR_H

#include <iostream>
#include <string>
#include <NOISE/noise.h>
#include "noiseutils.h"
#include <GL/glew.h>
#include <NOISE/module/modulebase.h>

class TextureGenerator
{
public:
	TextureGenerator();
	~TextureGenerator();

	void GenerateTexture();

	enum
	{
		RANDOM_TEX_0,
		RANDOM_TEX_1,
		RANDOM_TEX_2,
		RANDOM_TEX_3,
		RANDOM_TEX_4,
		TEX_NUMBER
	};
};

#endif