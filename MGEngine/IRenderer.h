#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"
#include "IFramebuffer.h"

class IRenderer {
protected:
	virtual void _set_window_size_internal_(Vector2<int> size) = 0;
	virtual void _init_internal_(Vector2<int> size = Vector2<int>(0, 0)) = 0;
	virtual std::shared_ptr<IFramebuffer> _create_main_framebuffer_() = 0;

	std::vector<std::shared_ptr<IFramebuffer>> FBs;
public:
	virtual Vector2<int> get_window_size() = 0;
	virtual std::shared_ptr<IFramebuffer> create_framebuffer(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) = 0;
	virtual void clear_screen() = 0;

	virtual bool poll_events() = 0;
	virtual void draw(std::vector<std::shared_ptr<Mesh>>) = 0;
	virtual void shutdown() = 0;

	void bind_main_framebuffer() {
		FBs[0]->bind();
	}

	void set_window_size(Vector2<int> size) {
		_set_window_size_internal_(size);

		for (auto f : FBs) {
			if (f->get_resize_with_resolution()) {
				f->resize(size);
			}
		}
	}

	void add_framebuffer(std::shared_ptr<IFramebuffer> fb) {
		FBs.push_back(fb);
	}

	void init(Vector2<int> size = Vector2<int>(0, 0)) {
		if (size.x == 0 || size.y == 0) {
			ELOG_INFO("No window size provided, using default: ", 800, "x", 600);
			size.x = 800;
			size.y = 600;
		}

		_init_internal_(size);

		// Initialize default framebuffer
		auto fb = _create_main_framebuffer_();
		add_framebuffer(fb);
	}
};