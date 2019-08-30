#ifndef MYSHADER_H
#define MYSHADER_H

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <iostream>

// Headers used to manipulate data using vec/mat
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

class myShader
{
public:
	myShader();

	myShader(const char* , const char* );

	void use();

	void setBool(const std::string &, bool) const;

	void setInt(const std::string &, int) const;

	void setFloat(const std::string &, float) const;

	void setVec3(const std::string &, const GLfloat*) const;
	
	void setMat4(const std::string &, const GLfloat*) const;

	unsigned int ID;

	void buildProgram(unsigned int, unsigned int);

};

#endif