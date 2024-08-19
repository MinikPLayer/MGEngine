#pragma once
#include <vector>
#include <memory>
#include "Mesh.hpp"
#include "IFramebuffer.hpp"

enum class RenderBackends {
	OpenGL = 0
};

class IRenderer {
protected:
	virtual void _set_window_size_internal_(Vector2<int> size) = 0;
	virtual void _init_internal_(Vector2<int> size = Vector2<int>(0, 0)) = 0;
	virtual std::shared_ptr<IFramebuffer> _create_main_framebuffer_() = 0;
	virtual std::shared_ptr<IFramebuffer> _create_framebuffer_(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) = 0;

	virtual std::shared_ptr<IShader> _create_default_shader_() = 0;
	virtual std::shared_ptr<IShader> _create_shader_(std::string vertex, std::string fragment) = 0;
	friend std::shared_ptr<IShader> IShader::create_default();
	friend std::shared_ptr<IShader> IShader::create(std::string vertex, std::string fragment);

	std::vector<std::shared_ptr<IFramebuffer>> FBs;
public:
	virtual Vector2<int> get_main_screen_resolution() = 0;

	virtual void set_vertical_sync(bool enabled) = 0;
	virtual void set_window_title(std::string title) = 0;
	
	virtual Vector2<int> get_resolution() = 0;

	virtual void clear() = 0;

	virtual bool poll_events() = 0;
	virtual void draw(std::vector<std::shared_ptr<Mesh>>) = 0;
	virtual void shutdown() = 0;

	virtual RenderBackends get_backend_type() = 0;

	std::shared_ptr<IFramebuffer> create_framebuffer(IFramebuffer::AttachmentTypes attachments, bool resize_with_window) {
		auto size = get_resolution();
		return _create_framebuffer_(attachments, resize_with_window, size);
	}

	void bind_screen_framebuffer() {
		FBs[0]->bind();
	}

	void bind_main_draw_framebuffer() {
		FBs[1]->bind();
	}

	void bind_postprocess_color_texture(unsigned int slot = 0) {
		FBs[1]->bind_color_attachment(slot);
	}

	void clear_screen() {
		bind_screen_framebuffer();
		clear();
	}

	void set_resolution(Vector2<int> size) {
		if (this->get_resolution().is_equal_exact(size))
			return;

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

		// Create framebuffer for drawing
		// It is used as a temporary buffer to allow postprocessing
		auto drawFb = _create_framebuffer_(IFramebuffer::AttachmentTypes::COLOR_DEPTH_STENCIL, true, get_resolution());
		add_framebuffer(drawFb);
	}
};