/*
OBJLoader for the class of Computer Graphics at Unisinos 2016/1
Obs.:By now this project is not ready. The idea is to implement all PBR rendering system.
Objective: Create a FREE OPENSOURCE PBR Scene Renderer for 3D Artists
Prof.: Rafael Hocevar
Author: Vinícius Pereira

TODO: Implement the option of calculate the mesh normals, ACEPT mesh withou normals or without texture coordinates
*/

#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "Manager.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

#undef main
int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Shader shader("../res/basicShader");
	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.01f, 1000.0f);

	Manager manager;
	manager.CreateObject("../res/cube.obj", "../res/box.jpg", "../res/box.jpg", &shader);
	manager.CreateObject("../res/cube.obj", "../res/noTexture.png", "../res/noTexture.png", &shader);


	/*Asset a, b;
	a.SetMesh("../res/cube.obj");
	a.SetShader(&shader);

	Material m, n;
	m.SetDiffuse("../res/box.jpg");
	m.SetSpecular("../res/box.jpg");

	a.SetMaterial(m);

	b.SetMesh("../res/cube.obj");
	b.SetShader(&shader);

	n.SetDiffuse("../res/noTexture.png");
	n.SetSpecular("../res/noTexture.png");

	b.SetMaterial(n);*/


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

		glm::vec3 lightPos(0.0, 0.0, 0.0);

		//Material
		//glUniform3f(glGetUniformLocation(shader.Program(), "material.ambient"), 1.0, 0.5, 0.31);
		//glUniform3f(glGetUniformLocation(shader.Program(), "material.diffuse"), 1.0, 0.5, 0.31);
		//glUniform3f(glGetUniformLocation(shader.Program(), "material.specular"), 0.5, 0.5, 0.5);
		//glUniform1f(glGetUniformLocation(shader.Program(), "material.shininess"), 0.5);		

		//Light
		glUniform3f(glGetUniformLocation(shader.Program(), "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.ambient"), 0.8, 0.8, 0.8);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.diffuse"), 0.5, 0.5, 0.5);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.specular"), 1.0, 1.0, 1.0);

		manager.DrawObjects(camera);
		/*a.SetPos(glm::vec3(1.0, 0.0, 5.0));
		a.Draw(camera);

		b.SetPos(glm::vec3(-1.0,0.0,5.0));
		b.Draw(camera);*/

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}

	return 0;
}