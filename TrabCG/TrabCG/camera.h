#ifndef CAMERA_H
#define CAMERA_H

#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GL/glew.h>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
		m_speed = 10;
	};

	inline glm::mat4 GetViewProjection() const {
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
		//return m_perspective * glm::lookAt(m_position, , m_up);
	};

	GLfloat getSpeed() { return m_speed; };
	void setSpeed(GLfloat newSpeed) { m_speed = newSpeed; };
	glm::vec3 position() { return m_position; };
	void setPosition(glm::vec3 newPos) { m_position = newPos; };

	void setForward(glm::vec3 value) { m_forward = value; };
protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	GLfloat m_speed;
};

#endif