
#ifndef TEXTURE2DLOADER_H
#define TEXTURE2DLOADER_H

#include <string>
#include <GLFW/glfw3.h>
#include <glad.h>

class texture2DLoader {

public:
	texture2DLoader();
	texture2DLoader(const char* , int , int , int , int , int , int );
	void bindTex(int);

private:
	unsigned int texture;
	void pickWrap(int, bool);
	GLint wrap;
	GLint scaler;
	unsigned char *data;
};


#endif
