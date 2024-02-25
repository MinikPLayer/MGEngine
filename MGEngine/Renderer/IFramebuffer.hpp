#pragma once

#include "..\..\Vector2.hpp"

class IFramebuffer {
public:
	// TODO: Add support for custom attachments list
	enum AttachmentTypes {
		COLOR = 0b1,
		DEPTH_STENCIL = 0b10,
		COLOR_DEPTH_STENCIL = COLOR | DEPTH_STENCIL,
	};

protected:
	bool main = false;
	bool resize_with_resolution = false;
	AttachmentTypes attachments;

	virtual void _init_as_main_() = 0;
	virtual void _init_(AttachmentTypes attachments, Vector2<int> size) = 0;
public:
	virtual void resize(Vector2<int> size) = 0;
	
	virtual void bind_color_attachment(unsigned int slot) = 0;
	virtual unsigned int get_id() = 0;
	virtual void bind() = 0;

	AttachmentTypes get_attachments() {
		return attachments;
	}

	bool is_main() {
		return main;
	}

	bool get_resize_with_resolution() {
		return resize_with_resolution;
	}

	bool set_resize_with_resolution(bool value) {
		resize_with_resolution = value;
	}

	void init(AttachmentTypes attachments, bool resize_with_resolution, Vector2<int> size) {
		this->resize_with_resolution = resize_with_resolution;
		this->attachments = attachments;
		_init_(attachments, size);
	}

	void init_as_main() {
		this->resize_with_resolution = true;
		this->main = true;
		_init_as_main_();
	}
};