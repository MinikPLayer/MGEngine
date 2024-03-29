#include "Renderer/GL/GLTexture.hpp"
#include "Config.hpp"
#include "Log.hpp"

void GLTexture::_init_() {
	glGenTextures(1, &texture.get());
	bind(0);

	switch (channelCount)
	{
	case 1:
		textureType = GL_RED;
		break;
	case 2:
		textureType = GL_RG;
		break;
	case 3:
		textureType = GL_RGB;
		break;
	case 4:
		textureType = GL_RGBA;
		break;
	default:
		ELOG_WARNING("Unsupported channel count. Defaulting to RGB");
		textureType = GL_RGB;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, textureType, width, height, 0, textureType, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLTexture::_update_(uint8_t* data) {
	bind(0);
	glTexImage2D(GL_TEXTURE_2D, 0, textureType, width, height, 0, textureType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GLTexture::_dispose_() {
	texture = -1;
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

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture.get());
}
