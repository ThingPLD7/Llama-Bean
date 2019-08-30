#include "primitives.h"
#include "myShader.h"
#include "camera.h"
#include "texture2DLoader.h"

#include <GLFW/glfw3.h>
#include <glad.h>

#include <iostream>

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

primitives::primitives()
{
	myShader temp("happyBox_Vertex_Shader.glsl", "happyBox_Fragment_Shader.glsl");
	primitiveShader = temp;
	texture2DLoader tempTex("H:\\Program Files\\OpenGL Project Files\\Global Resources\\container.jpg", 1, 1, 1, 1, 0, 0);
	texture = tempTex;
}

void primitives::createBox(camera* ptrCam)
{
	setCamera(ptrCam);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// Will tell the class what it will be drawing since this class will be a generic file for all
	// of the different primitives that can be drawn.
	choice = 1;
}

void primitives::draw()
{
	glEnable(GL_DEPTH_TEST);
	texture.bindTex(0);

	primitiveShader.use();

	primitiveShader.setMat4("view", glm::value_ptr(fp_Camera->view));

	glBindVertexArray(VAO);

	if (choice == 1) {
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	}

	primitiveShader.setMat4("model", glm::value_ptr(model));
	primitiveShader.setMat4("projection", glm::value_ptr(proj));

	glDisable(GL_DEPTH_TEST);
}

void primitives::perspective(int width, int height, float fov)
{
	proj = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
}

void primitives::setCamera(camera* camAddress)
{
	fp_Camera = camAddress;
	
}
