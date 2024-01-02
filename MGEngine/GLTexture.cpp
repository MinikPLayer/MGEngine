#include "GLTexture.h"
#include "Config.h"
#include "Log.h"

void GLTexture::_init_(unsigned int width, unsigned int height) {
	glGenTextures(1, &texture.get());
	bind(0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLTexture::bind(unsigned int slot) {
#if SC_ERROR_ON
	GLint maxSlots = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots);
	if ((GLint)slot > maxSlots) {
		ELOG_ERROR("Texture slot is higher than available");
		return;
	}
#endif

	glBindTexture(GL_TEXTURE_2D + slot, texture.get());
}
