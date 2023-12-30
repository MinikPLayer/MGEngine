#pragma once

#include "ITexture.h"
#include "GL_RAII.h"

class GLTexture : public ITexture {
protected:
	GL_Texture texture;

	void _init_(unsigned int width, unsigned int height) override;

public:
	GLuint get_raw_texture() {
		return texture.get();
	}

	void bind() override;
};