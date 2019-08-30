#ifndef CONTROLMENU_H
#define CONTROLMENU_H

#include "hardUI.h"
#include "myShader.h"
//#include "buttonUI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class controlMenu {
private:
	hardUI toolUI;
	//buttonUI toolButt;
	bool editUIMode = true;
	float x_mouse;
	float y_mouse;
	int width;
	int height;

public:
	// This function will do nothing, a blank constructor for now.
	controlMenu();
	void generateUI(float, float, float, float, float, float, float, float);
	//void generateButt([...])??;
	void wait(float, float, int, int);
	void update(float , float);
	void draw();
	void end();
	void processMouseXY(float, float);

};


#endif

