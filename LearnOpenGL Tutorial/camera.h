#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

class camera {

	
private:
	// Variables that will be used to store information about the camera
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::vec3 cameraRight;
	float currentTime;
	float pastTime = 0;
	float cameraSpeed ;

	void updateView();

public:
	// Need to send the view to the shader
	glm::mat4 view;

	camera();
	void updateMouse();
	void frameTime();
	void moveFoward();
	void moveBackward();
	void moveRight();
	void moveLeft();
	
	// Can use this value to manipulate the speed of the camera
	float speedModifier = 2.5;


};



#endif
