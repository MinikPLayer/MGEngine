#pragma once

#include "IFramebuffer.h"
#include "GL_RAII.h"
#include "GLTexture.h"

class GLFramebuffer : public IFramebuffer {
	GL_FBO fbo = -1;

	std::optional<GLTexture> color_attachment = std::nullopt;
	std::optional<GL_RBO> depth_stencil_attachment = std::nullopt;

protected:
	void _init_(AttachmentTypes attachments, Vector2<int> size) override;
	void _init_as_main_() override;

	void _manual_dispose_();
public:
	void bind_color_attachment(unsigned int slot) override;

	unsigned int get_id() override;

	void bind() override;
	void resize(Vector2<int> size) override;
};