#pragma once

#include "Renderer/ITexture.hpp"
#include "Renderer/GL/GL_RAII.hpp"

class GLTexture : public ITexture {
protected:
	GL_Texture texture = -1;
	unsigned int textureType = -1;

	void _init_() override;
	void _update_(uint8_t* data) override;
	void _dispose_() override;

public:
	GLuint get_raw_texture() {
		return texture.get();
	}

	void bind(unsigned int slot) override;

	void dispose() {
		texture.dispose();
	}
};