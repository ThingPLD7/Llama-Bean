#include "hardUI.h"
#include "myShader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <iomanip>

// Constructor Default
hardUI::hardUI() {
	//do nothing
}

// Deconstrutor
void hardUI::deconstructor() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &borderVAO);
	glDeleteBuffers(1, &borderVBO);
	glDeleteBuffers(1, &borderEBO);
}

// Constructor
	// First the constructor assigns the input values to the variables held by the class.
	// Next the constructor takes those values and creates an array.
	// This constructor will take in the inital values for the UI boxes and create the box with VAO, VBO.
hardUI::hardUI(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	// Will be used in buildVertices
	createOnce = true;
	 
	ourShader = myShader::myShader("hardUI_Vert_Shader.glsl", "hardUI_Frag_Shader.glsl");

	// Assign Variables to easily access them from main.
	// Top Left
	tLx_1 = x1;
	tLy_1 = y1;
	// Top Right
	tRx_2 = x2;
	tRy_2 = y2;
	// Bot Right
	bRx_3 = x3;
	bRy_3 = y3;
	// Bot Left
	bLx_4 = x4;
	bLy_4 = y4;

	// Assign array with Variables delcared above.
	buildVertices();
	build_BorderVertices();

	// Create the VAO object for the contex of the binding the VBO and the Attribute Pointer.
	buildObjects();
	build_BorderObjects();

}


// xMouse and yMouse need to be processed before it can just be added to the vertices.
void hardUI::resizeUI(float xMouse, float yMouse)
{
	enum Position {TOP, RIGHT, LEFT, BOTTOM};
	
//////////////////////////////////////////////////////////////
// Forces the 
	if (yMouse > 1)
		yMouse = 1;
	if (yMouse < -1)
		yMouse = -1;
	if (xMouse > 1)
		xMouse = 1;
	if (xMouse < -1)
		xMouse = -1;
//////////////////////////////////////////////////////////////

	switch (tRLB_choice) {
	case 0:
		tLy_1 = yMouse;
		tRy_2 = yMouse;
		break;
	case 1:
		tRx_2 = xMouse;
		bRx_3 = xMouse;
		break;
	case 2:
		tLx_1 = xMouse;
		bLx_4 = xMouse;
		break;
	case 3:
		bRy_3 = yMouse;
		bLy_4 = yMouse;
		break;
	default:
		std::cout << "FAILED::RESIZE::THE INT VALUE WAS NOT 0, 1, 2, OR 3\n";
		break;
	}

	// Rebuild the Vertices to be ready to be re-created into VAO, VBO, Attribute Pointer.
	buildVertices();
	build_BorderVertices();

	// Builds the VAO, VBO, and Attribute Pointer with new context.
	buildObjects();
	build_BorderObjects();

	tRLB_choice = 5;
}

// *****I think tmpVertices & tmpIndices needs to be changed to a dynamic pointer to ensure that the a memory leak does
// not happen!!*****
void hardUI::buildVertices()
{
	// Assign array with Variables delcared above.
	float tmpVertices[12] =
	{	tLx_1, tLy_1, 0.0f,		// Top Left 
		tRx_2, tRy_2, 0.0f,		// Top Right
		bRx_3, bRy_3, 0.0f,		// Bot Right
		bLx_4, bLy_4, 0.0f		// Bot Left
	};		

	for (int i = 0; i < 12; i++) {
		vertices[i] = tmpVertices[i];
	}

	if (createOnce) {
		float tmpIndices[6] =
		{
			0, 1, 2,		
			0, 2, 3			
		};

		for (int i = 0; i < 6; i++) {
			indices[i] = tmpIndices[i];
		}
		createOnce = false;
	}
}

void hardUI::buildObjects()
{
	// Create the VAO object for the contex of the binding the VBO and the Attribute Pointer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generates the Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Generate the Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the Vertex Attribute for the VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

// Call this function in the render loop to draw the box.
void hardUI::drawUI() {

	ourShader.use();

	// Gives
	int FragColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
	glUniform4f(FragColorLocation, 0.525f, 0.525f, 0.525f, 1.0f);

	// Binds the Vertex Array Object
	glBindVertexArray(VAO);
	// Executes the draw command
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
	int FragColorLocation2 = glGetUniformLocation(ourShader.ID, "ourColor");
	glUniform4f(FragColorLocation2, 0.3f, 0.3f, 0.3f, 1.0f);
	glBindVertexArray(borderVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	

 }


void hardUI::build_BorderVertices() {
	// Create Top Border
	float tmpVertices1[12] =
	{ 
		tLx_1 + variance, tLy_1 - variance, 0.0f,		// Top Left 
		tRx_2 - variance, tRy_2 - variance, 0.0f,		// Top Right
		bRx_3 - variance, bRy_3 + variance, 0.0f,		// Bot Right
		bLx_4 + variance, bLy_4 + variance, 0.0f		// Bot Left
	};

	for (int i = 0; i < 12; i++) {
		innerBorder[i] = tmpVertices1[i];
	}	

}

void hardUI::build_BorderObjects() {
	
	// Create the VAO object for the contex of the binding the VBO and the Attribute Pointer
	glGenVertexArrays(1, &borderVAO);
	glBindVertexArray(borderVAO);

	// Generates the Vertex Buffer Object
	glGenBuffers(1, &borderVBO);
	glBindBuffer(GL_ARRAY_BUFFER, borderVBO);
		
	glBufferData(GL_ARRAY_BUFFER, sizeof(innerBorder), innerBorder, GL_STATIC_DRAW);

	// Generate the Element Buffer Object
	glGenBuffers(1, &borderEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, borderEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the Vertex Attribute for the VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	


}

void hardUI::checkElement(float x, float y)
{
	bool output = false;
///////////////////////////////////////////---TESTING---///////////////////////////////////////////////////////////////
	/*
	if (false) {
	std::cout << "If top is true: " << vertices[0] << " < " << x << " < " << vertices[3] << std::endl;
	std::cout << "If top is true: " << innerBorder[1] << " < " << y << " < " << vertices[1] << std::endl;
	}
	if (false) {
		std::cout << "If left is true: " << vertices[0] << " < " << x << " < " << innerBorder[0] << std::endl;
		std::cout << "If left is true: " << vertices[1] << " < " << y << " < " << vertices[10] << std::endl;
	}
	if (false) {
		std::cout << "If bot is true: " << vertices[9] << " < " << x << " < " << vertices[6] << std::endl;
		std::cout << "If bot is true: " << innerBorder[7] << " < " << y << " < " << vertices[7] << std::endl;

	}
	*/
///////////////////////////////////////////---TESTING---///////////////////////////////////////////////////////////////	

	// Select: Top if True
	if ((vertices[0] - variance <= x && x <= vertices[3] + variance) && (innerBorder[1] - variance <= y && y <= vertices[1] + variance)) {
		tRLB_choice = 0;
		borderSelected = true;
		if(output)
			std::cout << "Top has been selected\n";
	}
	// Select: Right if True
	if (innerBorder[3] - variance <= x && x <= vertices[3] + variance && vertices[7] - variance <= y && y <= innerBorder[4] + variance) {
		tRLB_choice = 1;
		borderSelected = true;
		if(output)
			std::cout << "Right has been selected\n";
	}
	// Select: Bottom if True
	if (vertices[9] - variance <= x && x <= vertices[6] + variance && innerBorder[7] - variance <= y && y <= vertices[7] + variance) {
		tRLB_choice = 3;
		borderSelected = true;
		if(output)
			std::cout << "Bottom has been selected\n";
	}
	// Select: Left if True
	if (vertices[0] - variance <= x && x <= innerBorder[0] + variance && vertices[10] - variance <= y && y <= vertices[1] + variance) {
		tRLB_choice = 2;
		borderSelected = true;
		if(output)
			std::cout << "Left has been selected\n";
	}

}



