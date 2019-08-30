#include "controlMenu.h"
#include "hardUI.h"
#include "myShader.h"

#include <iostream>


controlMenu::controlMenu()
{
	hardUI toolUI;
}

void controlMenu::generateUI(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	toolUI = hardUI::hardUI(x1, y1, x2, y2, x3, y3, x4, y4);
	
}

void controlMenu::wait(float f_cl_x, float f_cl_y, int tmpWidth, int tmpHeight)
{
	width = tmpWidth;
	height = tmpHeight;
	// Output of the x and y value
	//std::cout << "The value is " << f_cl_x << " and " << f_cl_y << std::endl;
	processMouseXY(f_cl_x, f_cl_y);
	if (editUIMode) {
		toolUI.checkElement(x_mouse, y_mouse);
	}
}

void controlMenu::update(float r_cl_x, float r_cl_y)
{
	processMouseXY(r_cl_x, r_cl_y);
	// Output of the x and y value of the post processed values
	//std::cout << "The value is " << x_mouse << " and " << y_mouse << std::endl;
	if (toolUI.borderSelected && editUIMode) {
		toolUI.resizeUI(x_mouse, y_mouse);
		toolUI.borderSelected = false;
	}
}

void controlMenu::draw()
{
	toolUI.drawUI();
}

void controlMenu::processMouseXY(float x, float y)
{
	x_mouse = x / (width/2) - 1;
	y_mouse = (((height-1) - y) / (height/2)) - 1;
	
	// Output of the x and y value
	//std::cout << "The new value of x is: " << x_mouse << " and the new value of y is: " << y_mouse << std::endl;
}

void controlMenu::end() {
	toolUI.deconstructor();
}