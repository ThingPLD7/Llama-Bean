#ifndef HARDUI_H
#define HARDUI_H

#include <vector>
#include "myShader.h"


class hardUI {
public:
//-----------------------------------------------------------------------------------------------------------------
	// Variables
		// These variables will hold the values for the UI boxes.
	float tLx_1, tLy_1, tRx_2, tRy_2, bRx_3, bRy_3, bLx_4, bLy_4;
		// These variables will take values in and augment the UI boxes to change there size.
	float resizeX, resizeY;
		//This will hold the values of the UI box in an Array.
	float vertices[12];

	// Shader Objects
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// Boolean
		// Will be false until the user correctly selects the border
	bool borderSelected = false;
		
//-----------------------------------------------------------------------------------------------------------------
	// Functions
		// Constructor
	hardUI();
		// This constructor will take in the inital values for the UI boxes and create the box with VAO, VBO.
	hardUI(float, float, float, float, float, float, float, float);
		// This  function sends the x and y values along with the int which should be 0, 1, 2, or 3.
	void resizeUI(float, float);
	void buildVertices();
	void buildObjects();
	void drawUI();
		// This function to see if the position of x and y are on the border.
	void checkElement(float, float);
	
		// Deconstructor
	void deconstructor();
	
private:
	int indices[6];

	// This will hold whether the value is top, right, bottom, or left.
	int tRLB_choice = 5;

	// This bool ensures that the indices are only created once.
	bool createOnce;

	// This two unsigned ints will hold the objects that will create the border around the UI.
	unsigned int borderVBO;
	unsigned int borderVAO;
	unsigned int borderEBO;

	// These two functions will create the vertices that will be used to create the border.
	void build_BorderVertices();
		// This function will get the object ready to be drawn.
	void build_BorderObjects();

	// Arrays to hold Vertices
	// Top
	float innerBorder[12];

	myShader ourShader;

	// This variable is used to create the inside element of the UI border.
	float variance = 0.01;

	// Holds the click and release
	float xClick, yClick;
	float xRelease, yRelease;

};
#endif