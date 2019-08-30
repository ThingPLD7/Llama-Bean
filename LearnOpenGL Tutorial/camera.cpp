#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

camera::camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void camera::updateMouse()
{
}

void camera::frameTime()
{
	float delta;
	currentTime = glfwGetTime();
	delta = currentTime - pastTime;
	pastTime = currentTime;
	cameraSpeed = speedModifier * delta;
}

void camera::moveFoward()
{
	frameTime();
	cameraPos += cameraSpeed * cameraFront;
	updateView();
}

void camera::moveBackward()
{
	frameTime();
	cameraPos -= cameraSpeed * cameraFront;
	updateView();
}

void camera::moveRight()
{
	frameTime();
	cameraPos += cameraSpeed * cameraRight;
	updateView();
}

void camera::moveLeft()
{
	frameTime();
	cameraPos -= cameraSpeed * cameraRight;
	updateView();
}

void camera::updateView()
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
