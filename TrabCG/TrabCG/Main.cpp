/*
OBJLoader for the class of Computer Graphics at Unisinos 2016/1
Obs.:By now this project is not ready. The idea is to implement all PBR rendering system.
Objective: Create a FREE OPENSOURCE PBR Scene Renderer for 3D Artists
Prof.: Rafael Hocevar
Author: Vinícius Pereira

TODO: Implement the option of calculate the mesh normals, ACEPT mesh withou normals or without texture coordinates
*/

#include <iostream>
#include <NOISE/noise.h>
#include "noiseutils.h"
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "Manager.h"
#include "TextureGenerator.h"

using namespace noise;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

GLint m_mouseX, m_mouseY;
GLint lastX = 400, lastY = 300;
GLfloat yaw;
GLfloat pitch;
Camera camera(glm::vec3(0, 1, -10), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.01f, 1000.0f);

enum
{
	TOTAL_BUTTONS
};

void mouse_callback(double xpos, double ypos);

#undef main
int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Shader shader("../res/basicShader");

	Manager manager;
	manager.CreateObject("../res/cube.obj", "../res/box.jpg", "../res/box.jpg", &shader);
	manager.ObjectList[0].SetPos(glm::vec3(0, 1, 0));
	manager.CreateObject("../res/plane.obj", "../res/bricks.jpg", "../res/bricks.jpg", &shader);
	//manager.CreateObject("../res/cube.obj", "../res/noTexture.png", "../res/noTexture.png", &shader);

	TextureGenerator tg;
	tg.GenerateTexture();

	SDL_Event e;

	bool isRunning = true;
	float counter = 0.0f;
	while (isRunning)
	{
		GLuint currentFrame = SDL_GetTicks();
		deltaTime = (currentFrame - lastFrame) / 1000;
		lastFrame = currentFrame;


		GLfloat xoffset = m_mouseX - lastX;
		GLfloat yoffset = lastY - m_mouseY; // Reversed since y-coordinates range from bottom to top
		lastX = m_mouseX;
		lastY = m_mouseY;

		GLfloat sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;


		while (SDL_PollEvent(&e))
		{
			switch (e.type) {
			case SDL_KEYDOWN:
				//Key Press
				switch (e.key.keysym.sym) {
				case SDLK_1:
					printf("1");
					manager.SetRandomMaterial(0);
					break;
				case SDLK_2:
					printf("2");
					manager.SetRandomMaterial(1);
					break;
				case SDLK_3:
					printf("3");
					manager.SetRandomMaterial(2);
					break;
				case SDLK_4:
					printf("4");
					manager.SetRandomMaterial(3);
					break;
				case SDLK_5:
					printf("5");
					manager.SetRandomMaterial(4);
					break;
				case SDLK_w:
					camera.setPosition(glm::vec3(camera.position().x, camera.position().y, camera.position().z + (camera.getSpeed() * deltaTime)));
					break;
				case SDLK_s:
					camera.setPosition(glm::vec3(camera.position().x, camera.position().y, camera.position().z - (camera.getSpeed() * deltaTime)));
					break;
				case SDLK_a:
					camera.setPosition(glm::vec3(camera.position().x + (camera.getSpeed() * deltaTime), camera.position().y, camera.position().z));
					break;
				case SDLK_d:
					camera.setPosition(glm::vec3(camera.position().x - (camera.getSpeed() * deltaTime), camera.position().y, camera.position().z));
					break;

				case SDLK_ESCAPE:
					isRunning = false;
					break;
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				//Key Release
				break;
				
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&m_mouseX, &m_mouseY);
				mouse_callback(m_mouseX, m_mouseY);
				break;

			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}				
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

		//camera.setPosition(glm::vec3(camera.position().x, sin(counter) * 4, camera.position().z));

		display.SwapBuffers();
		SDL_Delay(1);
		counter += 0.01f;
	}

	return 0;
}

void mouse_callback(double xpos, double ypos)
{
	/*if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}*/

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//camera.setForward(glm::normalize(front));
}