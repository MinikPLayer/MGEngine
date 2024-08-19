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

enum class Keyboard {
	ARROW_LEFT = GLFW_KEY_LEFT,
	ARROW_RIGHT = GLFW_KEY_RIGHT,
	ARROW_UP = GLFW_KEY_UP,
	ARROW_DOWN = GLFW_KEY_DOWN,
	SPACE = GLFW_KEY_SPACE,
	ESCAPE = GLFW_KEY_ESCAPE,
	ENTER = GLFW_KEY_ENTER,
	UNKNOWN = -1,
	KEY_A = GLFW_KEY_A,
	KEY_B = GLFW_KEY_B,
	KEY_C = GLFW_KEY_C,
	KEY_D = GLFW_KEY_D,
	KEY_E = GLFW_KEY_E,
	KEY_F = GLFW_KEY_F,
	KEY_G = GLFW_KEY_G,
	KEY_H = GLFW_KEY_H,
	KEY_I = GLFW_KEY_I,
	KEY_J = GLFW_KEY_J,
	KEY_K = GLFW_KEY_K,
	KEY_L = GLFW_KEY_L,
	KEY_M = GLFW_KEY_M,
	KEY_N = GLFW_KEY_N,
	KEY_O = GLFW_KEY_O,
	KEY_P = GLFW_KEY_P,
	KEY_Q = GLFW_KEY_Q,
	KEY_R = GLFW_KEY_R,
	KEY_S = GLFW_KEY_S,
	KEY_T = GLFW_KEY_T,
	KEY_U = GLFW_KEY_U,
	KEY_V = GLFW_KEY_V,
	KEY_W = GLFW_KEY_W,
	KEY_X = GLFW_KEY_X,
	KEY_Y = GLFW_KEY_Y,
	KEY_Z = GLFW_KEY_Z,
	KEY_0 = GLFW_KEY_0,
	KEY_1 = GLFW_KEY_1,
	KEY_2 = GLFW_KEY_2,
	KEY_3 = GLFW_KEY_3,
	KEY_4 = GLFW_KEY_4,
	KEY_5 = GLFW_KEY_5,
	KEY_6 = GLFW_KEY_6,
	KEY_7 = GLFW_KEY_7,
	KEY_8 = GLFW_KEY_8,
	KEY_9 = GLFW_KEY_9,
	KEY_F1 = GLFW_KEY_F1,
	KEY_F2 = GLFW_KEY_F2,
	KEY_F3 = GLFW_KEY_F3,
	KEY_F4 = GLFW_KEY_F4,
	KEY_F5 = GLFW_KEY_F5,
	KEY_F6 = GLFW_KEY_F6,
	KEY_F7 = GLFW_KEY_F7,
	KEY_F8 = GLFW_KEY_F8,
	KEY_F9 = GLFW_KEY_F9,
	KEY_F10 = GLFW_KEY_F10,
	KEY_F11 = GLFW_KEY_F11,
	KEY_F12 = GLFW_KEY_F12,
	KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
	KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
	KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
	KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
	KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
	KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
	KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
	KEY_TAB = GLFW_KEY_TAB,
	KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
	KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
	KEY_DELETE = GLFW_KEY_DELETE,
	KEY_INSERT = GLFW_KEY_INSERT,
	KEY_HOME = GLFW_KEY_HOME,
	KEY_END = GLFW_KEY_END,
	KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
	KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
	KEY_KP_0 = GLFW_KEY_KP_0,
	KEY_KP_1 = GLFW_KEY_KP_1,
	KEY_KP_2 = GLFW_KEY_KP_2,
	KEY_KP_3 = GLFW_KEY_KP_3,
	KEY_KP_4 = GLFW_KEY_KP_4,
	KEY_KP_5 = GLFW_KEY_KP_5,
	KEY_KP_6 = GLFW_KEY_KP_6,
	KEY_KP_7 = GLFW_KEY_KP_7,
	KEY_KP_8 = GLFW_KEY_KP_8,
	KEY_KP_9 = GLFW_KEY_KP_9,
	KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
	KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
	KEY_KP_ADD = GLFW_KEY_KP_ADD,
	KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
	KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
	KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
	KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
	KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
	KEY_PAUSE = GLFW_KEY_PAUSE,
	KEY_MENU = GLFW_KEY_MENU,
	KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
	KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
	KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
	KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
	KEY_COMMA = GLFW_KEY_COMMA,
	KEY_PERIOD = GLFW_KEY_PERIOD,
	KEY_SLASH = GLFW_KEY_SLASH,
	KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
	KEY_MINUS = GLFW_KEY_MINUS,
	KEY_EQUAL = GLFW_KEY_EQUAL,
	KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
	KEY_WORLD_1 = GLFW_KEY_WORLD_1,
	KEY_WORLD_2 = GLFW_KEY_WORLD_2,
	KEY_SIHFT_LEFT = GLFW_KEY_LEFT_SHIFT,
	KEY_CONTROL_LEFT = GLFW_KEY_LEFT_CONTROL,
	KEY_ALT_LEFT = GLFW_KEY_LEFT_ALT,
	KEY_SUPER_LEFT = GLFW_KEY_LEFT_SUPER,
	KEY_SHIFT_RIGHT = GLFW_KEY_RIGHT_SHIFT,
	KEY_CONTROL_RIGHT = GLFW_KEY_RIGHT_CONTROL,
	KEY_ALT_RIGHT = GLFW_KEY_RIGHT_ALT,
	KEY_SUPER_RIGHT = GLFW_KEY_RIGHT_SUPER,
};

enum class MouseAxis {
	UNKNOWN,
	X,
	Y,
	ScrollX,
	ScrollY
};

enum class InputDevices {
	Keyboard,
	Joystick, // Not implemented
	Mouse
};

enum class CursorModes {
	Normal = GLFW_CURSOR_NORMAL,
	Hidden = GLFW_CURSOR_HIDDEN,
	Disabled = GLFW_CURSOR_DISABLED
};

struct InputMappingSettings {
	float multiplier = 1.0f;
	float deadzone = 0.0f;
	bool inverted = false;

	float getValue(float x) {
		int sign = inverted ? -FloatUtils::Sign(x) : FloatUtils::Sign(x);
		float abs = std::abs(x);
		float val = (abs - deadzone) / (1.0f - deadzone);
		if (val < 0)
			val = 0;

		return sign * val * multiplier;
	}

	InputMappingSettings(float multiplier = 1, float deadzone = 0, bool inverted = 0) {
		this->multiplier = multiplier;
		this->deadzone = deadzone;
		this->inverted = inverted;
	}
};

class InputMapping {
	float value = 0;
	float lastValue = 0;

	std::string name;
	InputDevices device;

	Keyboard positiveKey = Keyboard::UNKNOWN;
	Keyboard negativeKey = Keyboard::UNKNOWN;

	MouseAxis mouseAxis = MouseAxis::UNKNOWN;

	InputMappingSettings settings;
public:
	InputDevices get_device() {
		return device;
	}

	std::string get_name() {
		return name;
	}

	void update(GLFWwindow* window, Vector2<float> mouseMovement, float scrollDeltaX, float scrollDeltaY) {
		float ret = 0;
		switch (device) {
		case InputDevices::Keyboard:
			if (positiveKey != Keyboard::UNKNOWN) {
				ret = glfwGetKey(window, (int)positiveKey) == GLFW_PRESS ? 1.0f : 0.0f;
			}

			if (negativeKey != Keyboard::UNKNOWN) {
				ret -= glfwGetKey(window, (int)negativeKey) == GLFW_PRESS ? 1.0f : 0.0f;
			}
			break;

		case InputDevices::Mouse:
			if (mouseAxis != MouseAxis::UNKNOWN) {
				switch (mouseAxis) {
				case MouseAxis::X:
					ret = mouseMovement.x;
					break;
				case MouseAxis::Y:
					ret = mouseMovement.y;
					break;
				case MouseAxis::ScrollX:
					ret = scrollDeltaX;
					break;
				case MouseAxis::ScrollY:
					ret = scrollDeltaY;
					break;
				}
			}
			break;
		case InputDevices::Joystick:
			ELOG_FATAL("Not implemented");
			break;
		}

		ret = settings.getValue(ret);
		lastValue = this->value;
		this->value = ret;
	}

	bool is_pressed() {
		return value >= 0.5f;
	}

	float get_value() {
		return value;
	}

	bool is_just_pressed() {
		return is_pressed() && (lastValue < 0.5f);
	}

	InputMapping(std::string name, Keyboard positiveKey, Keyboard negativeKey = Keyboard::UNKNOWN, InputMappingSettings settings = InputMappingSettings()) {
		this->name = name;
		this->positiveKey = positiveKey;
		this->negativeKey = negativeKey;
		this->device = InputDevices::Keyboard;
		this->settings = settings;
	}

	InputMapping(std::string name, MouseAxis axis, InputMappingSettings settings = InputMappingSettings()) {
		this->name = name;
		this->mouseAxis = axis;
		this->device = InputDevices::Mouse;
		this->settings = settings;
	}
};

class GLFWInput {
	static int curMappingId;
	static std::map<int, InputMapping> idMappings;

	static std::map<std::string, int> nameToIdMappings;

	static Vector2<float> lastMousePos;
	static float scrollDeltaX;
	static float scrollDeltaY;

	static bool isInitialized;
	static CursorModes cursorMode;

	static void init(GLFWwindow* window);
public:
	static void __SetScroll(double x, double y) {
		scrollDeltaX += (float)x;
		scrollDeltaY += (float)y;
	}

	static void __Update(GLFWwindow* window) {
		if (!isInitialized) {
			init(window);
		}

		auto sdx = scrollDeltaX;
		auto sdy = scrollDeltaY;
		scrollDeltaX = 0;
		scrollDeltaY = 0;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		auto newPos = Vector2<float>((float)xpos, (float)ypos);
		auto mousePosDiff = newPos - lastMousePos;
		lastMousePos = newPos;
		for (auto it = idMappings.begin(); it != idMappings.end(); it++) {
			it->second.update(window, mousePosDiff, sdx, sdy);
		}

		glfwSetInputMode(window, GLFW_CURSOR, (int)cursorMode);
		if (cursorMode == CursorModes::Disabled && glfwRawMouseMotionSupported())
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		else
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
	}

	static void SetCursorMode(CursorModes mode) {
		cursorMode = mode;
	}

	static bool key_is_pressed(Keyboard key) {
		return glfwGetKey(glfwGetCurrentContext(), (int)key) == GLFW_PRESS;
	}

	// TODO: Add option to register multiple mappings with the same name (for different devices)
	static int register_mapping(InputMapping mapping) {
#if SC_WARNING_ON
		if (nameToIdMappings.contains(mapping.get_name())) {
			ELOG_WARNING("Mapping already exists: \"", mapping.get_name(), "\"");
		}
#endif	

		int id = curMappingId++;
		idMappings.insert({ id, mapping });
		nameToIdMappings.insert({ mapping.get_name(), id });

		return id;
	}

	static void update_mapping(InputMapping mapping) {
		auto id = get_id(mapping.get_name());
		if (!id.has_value()) {
			ELOG_ERROR("Trying to update mapping that doesn't exist (\"" + mapping.get_name() + "\"");
			return;
		}

		idMappings.at(id.value()) = mapping;
	}

	static std::optional<InputMapping> get(int id) {
		try {
			auto mapping = idMappings.at(id);
			return mapping;
		}
		catch (std::out_of_range) {
			ELOG_ERROR("Input id not found: ", id);
			return std::nullopt;
		};
	}

	static std::optional<int> get_id(std::string name) {
		int id = 0;
		try {
			id = nameToIdMappings.at(name);
		}
		catch (std::out_of_range) {
			ELOG_ERROR("Input name not found: \"", name, "\"");
			return std::nullopt;
		};
	}

	static std::optional<InputMapping> get(std::string name) {
		auto id = get_id(name);
		if (!id.has_value())
			return std::nullopt;

		return get(id.value());
	}

	static bool remove_mapping(int id) {
		auto mapping = get(id);
		if (!mapping.has_value())
			return false;

		idMappings.erase(id);
		nameToIdMappings.erase(mapping.value().get_name());
	}
};

#endif