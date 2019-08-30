
#include "texture2DLoader.h"
#include <string>
#include <stb_image.h>
#include <iostream>

texture2DLoader::texture2DLoader() {
	//do nothing
}

texture2DLoader::texture2DLoader(const char* tmpText, int param_S, int param_S_wrap, int param_T, int param_T_wrap, int filterMin, int filterMax)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (param_S == 1) {
		pickWrap(param_S_wrap, true);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	}
	if (param_T == 1) {
		pickWrap(param_T_wrap, true);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	}
	pickWrap(filterMin, false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaler);

	pickWrap(filterMax, false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaler);

	int width, height, nrChannels;
	data = stbi_load(tmpText, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);

}

void texture2DLoader::bindTex(int num)
{
	glActiveTexture(GL_TEXTURE0+num);
	glBindTexture(GL_TEXTURE, texture);
}

void texture2DLoader::pickWrap(int choice, bool wrapFilter)
{
	if (wrapFilter) {
		switch (choice) {
		case 0:
			wrap = GL_REPEAT;
			break;
		case 1:
			wrap = GL_MIRRORED_REPEAT;
			break;
		case 2:
			wrap = GL_CLAMP_TO_EDGE;
			break;
		case 3:
			wrap = GL_CLAMP_TO_BORDER;
			break;
		default:
			wrap = GL_REPEAT;
			std::cout << "No choice picked/invalid choice!" << std::endl;
			break;
		}
		choice = 5;
	}
	if (!wrapFilter) {
		if (choice == 0) {
			scaler = GL_LINEAR;
		}
		if (choice == 1) {
			scaler = GL_NEAREST;
		}
		choice = 5;
	}
}
