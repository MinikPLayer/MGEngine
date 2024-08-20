#pragma once

#ifdef INPUT_BACKEND_GLFW_SUPPORT

#include "GLInclude.hpp"
#include <GLFW/glfw3.h>
#include <map>
#include <string>
#include "Log.hpp"
#include <optional>
#include "Vector2.hpp"
#include <algorithm>
#include "IInputBackend.hpp"
#include "Input.hpp"

class GLFWInputBackend : public IInputBackend {
	std::weak_ptr<GLFWwindow> window;

public:
	GLFWInputBackend(std::weak_ptr<GLFWwindow> window);

	static int get_glfw_key_map(KeyboardKeys key);
	bool is_key_pressed(KeyboardKeys key) override;
	void set_cursor_mode(CursorModes mode) override;
	Vector2f get_cursor_position() override;
};

#endif