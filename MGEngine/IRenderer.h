#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"

class IRenderer {
public:
	virtual Vector2<int> get_window_size() = 0;
	virtual void set_window_size(Vector2<int> size) = 0;

	// TODO: Implement this
	// virtual void set_framebuffer_size(unsigned int width, unsigned int height) = 0;

	virtual void clear_screen() = 0;

	virtual bool poll_events() = 0;
	virtual void init(Vector2<int> size = Vector2<int>(0, 0)) = 0;
	virtual void draw(std::vector<std::weak_ptr<Mesh>>) = 0;
	virtual void shutdown() = 0;
};