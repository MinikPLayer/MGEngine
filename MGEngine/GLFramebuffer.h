#pragma once

#include "IFramebuffer.h"
#include "GL_RAII.h"

class GLFramebuffer : public IFramebuffer {
	GL_FBO fbo;

protected:
	void _init_(AttachmentTypes attachments) override;
	void _init_as_main_() override;
public:
	unsigned int get_id() override;

	void bind() override;
	void resize(Vector2<int> size) override;
};