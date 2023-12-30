#include "GLTexture.h"

void GLTexture::_init_(unsigned int width, unsigned int height) {
	glGenTextures(1, &texture.get());
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLTexture::bind() {
	glBindTexture(GL_TEXTURE_2D, texture.get());
}
