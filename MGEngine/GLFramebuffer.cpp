#include "GLFramebuffer.h"
#include "Config.h"
#include "Log.h"

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
	// TODO: Implement
	throw std::logic_error("Not implemented");
}

void GLFramebuffer::_init_(AttachmentTypes attachments) {
	glGenFramebuffers(1, &fbo.get());
	bind();
}

void GLFramebuffer::_init_as_main_() {
	fbo = 0;
}
