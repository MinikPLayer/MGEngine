#pragma once

#include "Vector2.h"

class IFramebuffer {
public:
	enum AttachmentTypes {
		COLOR = 0b1,
		DEPTH = 0b10,
		STENCIL = 0b100,
		COLOR_DEPTH = COLOR | DEPTH,
		COLOR_STENCIL = COLOR | STENCIL,
		DEPTH_STENCIL = DEPTH | STENCIL,
		COLOR_DEPTH_STENCIL = COLOR | DEPTH | STENCIL,
	};

protected:
	bool main = false;
	bool resize_with_resolution = false;

	virtual void _init_as_main_() = 0;
	virtual void _init_(AttachmentTypes attachments, Vector2<int> size) = 0;
public:

	virtual void resize(Vector2<int> size) = 0;
	virtual unsigned int get_id() = 0;

	virtual void bind() = 0;

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
		_init_(attachments, size);
	}

	void init_as_main() {
		this->resize_with_resolution = true;
		_init_as_main_();
	}
};