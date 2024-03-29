#pragma once

#include "Renderer/IFramebuffer.hpp"
#include "Renderer/GL/GL_RAII.hpp"
#include "Renderer/GL/GLTexture.hpp"
#include <memory>

class GLFramebuffer : public IFramebuffer {
	GL_FBO fbo = -1;

	std::unique_ptr<GLTexture> color_attachment = nullptr;
	std::unique_ptr<GL_RBO> depth_stencil_attachment = std::unique_ptr<GL_RBO>(new GL_RBO(-1));

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