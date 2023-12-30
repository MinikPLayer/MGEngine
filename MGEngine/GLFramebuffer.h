#pragma once

#include "IFramebuffer.h"
#include "GL_RAII.h"
#include "GLTexture.h"

class GLFramebuffer : public IFramebuffer {
	GL_FBO fbo;

	std::optional<GLTexture> color_attachment = std::nullopt;

protected:
	void _init_(AttachmentTypes attachments, Vector2<int> size) override;
	void _init_as_main_() override;
public:
	unsigned int get_id() override;

	void bind() override;
	void resize(Vector2<int> size) override;
};