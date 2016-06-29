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
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

#undef main
int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	/*Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5, 0.0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0,0.0))
	};

	unsigned int indices[] = {
		0, 1, 2
	};*/

	Mesh cubo("../res/cube.obj");
	Shader shader("../res/basicShader");
	Texture texture("../res/box.jpg");
	Texture texture2("../res/box2.png");
	Texture texture3("../res/box2-spec.png");
	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.01f, 1000.0f);
	Transform transform;

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

		transform.SetPos(glm::vec3(0.7,0,0));
		//transform.GetRot().x = sin(counter);
		//transform.GetRot().y = counter;
		transform.SetScale(glm::vec3(0.4));

		shader.Bind();

		glm::vec3 lightPos(sin(counter), -cos(counter), 2.0f);

		glUniform1f(glGetUniformLocation(shader.Program(), "ambientStrength"), 1.0);
		glUniform3f(glGetUniformLocation(shader.Program(), "lightColor"), 1.0, 1.0, 1.0);
		glUniform3f(glGetUniformLocation(shader.Program(), "cameraPos"), camera.position().x, camera.position().y, camera.position().z);

		//Material
		//glUniform3f(glGetUniformLocation(shader.Program(), "material.ambient"), 1.0, 0.5, 0.31);
		//glUniform3f(glGetUniformLocation(shader.Program(), "material.diffuse"), 1.0, 0.5, 0.31);
		glUniform3f(glGetUniformLocation(shader.Program(), "material.specular"), 0.5, 0.5, 0.5);
		glUniform1f(glGetUniformLocation(shader.Program(), "material.shininess"), 32.0);

		//Directional Light
		glUniform3f(glGetUniformLocation(shader.Program(), "directionalLightDir"), -sin(counter), -1.0, -0.3);
		glUniform1f(glGetUniformLocation(shader.Program(), "directionalLightIntesity"), 10.0);
		glUniform3f(glGetUniformLocation(shader.Program(), "directionalLightPosition"), 0.0, 10.0, 0.0);
		
		

		//Light
		glUniform3f(glGetUniformLocation(shader.Program(), "light.position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.ambient"), 0.8, 0.8, 0.8);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.diffuse"), 0.5, 0.5, 0.5);
		glUniform3f(glGetUniformLocation(shader.Program(), "light.specular"), 1.0, 1.0, 1.0);


		texture2.Bind(0, shader);
		texture3.Bind(1, shader);
		shader.Update(transform, camera);
		cubo.Draw();

		texture3.Unbind();

		transform.SetPos(glm::vec3(-0.7, 0, 0));

		texture.Bind(0, shader);
		shader.Update(transform, camera);
		cubo.Draw();

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}

	return 0;
}