#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

#undef main
int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5, 0.0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0,0.0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("../res/basicShader");
	Texture texture("../res/bricks.jpg");

	SDL_Event e;
	bool isRunning = true;
	float counter = 0.0f;
	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				isRunning = false;
		}

		display.Clear(0.2f, 0.5f, 0.0f, 1.0f);

		shader.Bind();
		texture.Bind(0);
		mesh.Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}

	return 0;
}