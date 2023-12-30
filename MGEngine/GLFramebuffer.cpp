#include "GLFramebuffer.h"
#include "Config.h"
#include "Log.h"
#include "Engine.h"

unsigned int GLFramebuffer::get_id() {
	return fbo.get();
}

void GLFramebuffer::bind() {
#if !NDEBUG
	if (fbo.get() == -1 && !main) {
		ELOG_FATAL("Framebuffer not initialized!");
		exit(0x1FB);
	}
#endif

	glBindFramebuffer(GL_FRAMEBUFFER, fbo.get());
}

void GLFramebuffer::resize(Vector2<int> size) {
	// Main FB is automatically resized 
	// TODO: Check if glViewport should be called here
	if (main)
		return;

	_manual_dispose_();
	_init_(attachments, size);
}

void GLFramebuffer::_init_(AttachmentTypes attachments, Vector2<int> size) {
	glGenFramebuffers(1, &fbo.get());
	bind();

	// Create color attachment
	if ((attachments & AttachmentTypes::COLOR) == AttachmentTypes::COLOR) {
		color_attachment = GLTexture();
		color_attachment->init(size.x, size.y);

		// Bind color attachment to FB
		color_attachment->bind(0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment->get_raw_texture(), 0);
	}

	if ((attachments & (AttachmentTypes::DEPTH_STENCIL)) == AttachmentTypes::DEPTH_STENCIL) {
		depth_stencil_attachment = -1;
		glGenRenderbuffers(1, &depth_stencil_attachment.value().get());
		glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_attachment.value().get());

		// TODO: Add option to select Depth as a texture instead of RenderBuffer to improve performance when sampling
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_attachment.value().get());
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

void GLFramebuffer::_init_as_main_() {
	fbo = 0;
}

void GLFramebuffer::_manual_dispose_() {
	fbo = -1;
	color_attachment.reset();
	depth_stencil_attachment.reset();
}

void GLFramebuffer::bind_color_attachment(unsigned int slot) {
	if (!color_attachment.has_value()) {
		ELOG_FATAL("Trying to bind an empty FB color attachment.");
		Engine::stop();
		return;
	}

	color_attachment.value().bind(slot);
}
