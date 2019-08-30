#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "myShader.h"
#include "camera.h"
#include "texture2DLoader.h"

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

class primitives{
private:
	float boxVertices[64] = {
		// Vertices				// Colors				// Texcoords
		// Front Square
		//x		 //y	 //z	 //r	 //g	 //b	 //x	 //y
		0.5f,	 0.5f,	 0.5f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	// Top Right	// 0
		0.5f,	-0.5f,	 0.5f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	// Bot Right	// 1
	   -0.5f,	-0.5f,	 0.5f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	 0.0f,	// Bot Left		// 2
	   -0.5f,	 0.5f,	 0.5f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	 1.0f,	// Top Left		// 3

		// Back Square
		//x		 //y	 //z	 //r	 //g	 //b	 //x	 //y
		0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	// Top Right	// 4
		0.5f,	-0.5f,	-0.5f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	// Bot Right	// 5
	   -0.5f,	-0.5f,	-0.5f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	 0.0f,	// Bot Left		// 6
	   -0.5f,	 0.5f,	-0.5f,	 1.0f,	 1.0f,	 1.0f,	 0.0f,	 1.0f	// Top Left		// 7
	};

	int boxIndices[36] = {
		// Front Square
		0, 1, 2,	// triangle 1
		0, 2, 3,	// triangle 2

		// Right Square
		0, 1, 5,	// triangle 3
		0, 4, 5,	// triangle 4

		// Back Square
		4, 5, 6,	// triangle 5
		4, 6, 7,	// triangle 6

		// Left Square
		3, 2, 6,	// triangle 7
		3, 6, 7,	// triangle 8

		// Top Square
		0, 3, 7,	// triangle 9
		0, 4, 7,	// triangle 10

		//Bot Square
		1, 2, 6,	// triangle 11
		1, 5, 6		// triangle 12
	};

	unsigned int VAO, VBO, EBO;
	int choice = 5;

	myShader primitiveShader;
	camera* fp_Camera;
	texture2DLoader texture;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

public:
	primitives();
	void createBox(camera *);
	//void createSphere();
	//void createCone();
	//void createTorus();
	//void createCylinder();


	void draw();
	void perspective(int, int, float);
	void setCamera(camera *);
};





#endif
