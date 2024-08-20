#pragma once

#include "Vector2.hpp"
#include "InputStructs.hpp"

class IInputBackend {
	static Vector2f scroll_value;

protected:
	static void _scroll_callback_(Vector2f scrollDelta);

public:
	virtual bool is_key_pressed(KeyboardKeys key) = 0;
	virtual void set_cursor_mode(CursorModes mode) = 0;
	virtual Vector2f get_cursor_position() = 0;
	Vector2f get_scroll_value();
};
