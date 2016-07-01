#include "TextureGenerator.h"



TextureGenerator::TextureGenerator()
{
}


TextureGenerator::~TextureGenerator()
{
}

void TextureGenerator::GenerateTexture()
{
	for (GLint i = 0; i < TEX_NUMBER; i++)
	{
		//Random 2D Textures Gen

		module::Module* noise = new module::Perlin;

		switch (i)
		{
		case 0:
			noise = new module::Perlin;
			break;
		case 1:
			noise = new module::Voronoi;
			break;
		case 2:
			noise = new module::Billow;
			break;
		case 3:
			noise = new module::RidgedMulti;
			break;
		case 4:
			noise = new module::Spheres;
			break;
		}

		//noise->SetOctaveCount(6); // 6 is default
		//noise->SetFrequency(1); // 1 is default
		//noise->SetPersistence(0.5); // 0.5 is default

		utils::NoiseMap heightMap;
		utils::NoiseMapBuilderPlane heightMapBuilder;
		heightMapBuilder.SetSourceModule(*noise);
		heightMapBuilder.SetDestNoiseMap(heightMap);
		heightMapBuilder.SetDestSize(512, 512);
		heightMapBuilder.SetBounds(0.0, 10.0, 0.0, 10.0);
		heightMapBuilder.Build();

		utils::RendererImage renderer;
		utils::Image image;
		renderer.SetSourceNoiseMap(heightMap);
		renderer.SetDestImage(image);
		//Colors
		renderer.ClearGradient();
		renderer.AddGradientPoint(-1.0, utils::Color(0, 0, 128, 255)); //Deeps
		renderer.AddGradientPoint(-0.25, utils::Color(0, 0, 255, 255));//Shallow
		renderer.AddGradientPoint(0.0000, utils::Color(0, 128, 255, 255)); // shore
		renderer.AddGradientPoint(0.0625, utils::Color(240, 240, 64, 255)); // sand
		renderer.AddGradientPoint(0.1250, utils::Color(32, 160, 0, 255)); // grass
		renderer.AddGradientPoint(0.3750, utils::Color(224, 224, 0, 255)); // dirt
		renderer.AddGradientPoint(0.7500, utils::Color(128, 128, 128, 255)); // rock
		renderer.AddGradientPoint(1.0000, utils::Color(255, 255, 255, 255)); // snow

																			 //Fake light source
		renderer.EnableLight();
		renderer.SetLightContrast(3.0);
		renderer.SetLightBrightness(2.0);

		renderer.Render();

		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		std::string fileName = "noise" + std::to_string(i) + ".bmp";
		writer.SetDestFilename(fileName);
		writer.WriteDestFile();
	}
}
