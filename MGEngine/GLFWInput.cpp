#ifdef INPUT_BACKEND_GLFW_SUPPORT

#include "GLFWInput.hpp"

GLFWInputBackend::GLFWInputBackend(std::weak_ptr<GLFWwindow> window) {
	auto callback = [](GLFWwindow* window, double a, double b) {
		IInputBackend::_scroll_callback_(Vector2f((float)a, (float)b));
	};
	glfwSetScrollCallback(window.lock().get(), callback);

	this->window = window;
}

bool GLFWInputBackend::is_key_pressed(KeyboardKeys key) {
	auto glfwKey = get_glfw_key_map(key);
	return glfwGetKey(window.lock().get(), glfwKey) == GLFW_PRESS;
}

void GLFWInputBackend::set_cursor_mode(CursorModes mode) {
	switch (mode) {
	case CursorModes::Normal:
		glfwSetInputMode(window.lock().get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetInputMode(window.lock().get(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		break;
	case CursorModes::Hidden:
		glfwSetInputMode(window.lock().get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetInputMode(window.lock().get(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		break;
	case CursorModes::Disabled:
		glfwSetInputMode(window.lock().get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (glfwRawMouseMotionSupported()) {
			glfwSetInputMode(window.lock().get(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		break;
	default:
		ELOG_ERROR("Cursor mode ", (int)mode, " not found");
	}
}

Vector2f GLFWInputBackend::get_cursor_position() {
	double x, y;
	glfwGetCursorPos(window.lock().get(), &x, &y);
	return Vector2f((float)x, (float)y);
}

int GLFWInputBackend::get_glfw_key_map(KeyboardKeys key) {
	switch (key) {
	case KeyboardKeys::KEY_ARROW_LEFT:
		return GLFW_KEY_LEFT;
	case KeyboardKeys::KEY_ARROW_RIGHT:
		return GLFW_KEY_RIGHT;
	case KeyboardKeys::KEY_ARROW_UP:
		return GLFW_KEY_UP;
	case KeyboardKeys::KEY_ARROW_DOWN:
		return GLFW_KEY_DOWN;
	case KeyboardKeys::KEY_SPACE:
		return GLFW_KEY_SPACE;
	case KeyboardKeys::KEY_ESCAPE:
		return GLFW_KEY_ESCAPE;
	case KeyboardKeys::KEY_ENTER:
		return GLFW_KEY_ENTER;
	case KeyboardKeys::KEY_A:
		return GLFW_KEY_A;
	case KeyboardKeys::KEY_B:
		return GLFW_KEY_B;
	case KeyboardKeys::KEY_C:
		return GLFW_KEY_C;
	case KeyboardKeys::KEY_D:
		return GLFW_KEY_D;
	case KeyboardKeys::KEY_E:
		return GLFW_KEY_E;
	case KeyboardKeys::KEY_F:
		return GLFW_KEY_F;
	case KeyboardKeys::KEY_G:
		return GLFW_KEY_G;
	case KeyboardKeys::KEY_H:
		return GLFW_KEY_H;
	case KeyboardKeys::KEY_I:
		return GLFW_KEY_I;
	case KeyboardKeys::KEY_J:
		return GLFW_KEY_J;
	case KeyboardKeys::KEY_K:
		return GLFW_KEY_K;
	case KeyboardKeys::KEY_L:
		return GLFW_KEY_L;
	case KeyboardKeys::KEY_M:
		return GLFW_KEY_M;
	case KeyboardKeys::KEY_N:
		return GLFW_KEY_N;
	case KeyboardKeys::KEY_O:
		return GLFW_KEY_O;
	case KeyboardKeys::KEY_P:
		return GLFW_KEY_P;
	case KeyboardKeys::KEY_Q:
		return GLFW_KEY_Q;
	case KeyboardKeys::KEY_R:
		return GLFW_KEY_R;
	case KeyboardKeys::KEY_S:
		return GLFW_KEY_S;
	case KeyboardKeys::KEY_T:
		return GLFW_KEY_T;
	case KeyboardKeys::KEY_U:
		return GLFW_KEY_U;
	case KeyboardKeys::KEY_V:
		return GLFW_KEY_V;
	case KeyboardKeys::KEY_W:
		return GLFW_KEY_W;
	case KeyboardKeys::KEY_X:
		return GLFW_KEY_X;
	case KeyboardKeys::KEY_Y:
		return GLFW_KEY_Y;
	case KeyboardKeys::KEY_Z:
		return GLFW_KEY_Z;
	case KeyboardKeys::KEY_0:
		return GLFW_KEY_0;
	case KeyboardKeys::KEY_1:
		return GLFW_KEY_1;
	case KeyboardKeys::KEY_2:
		return GLFW_KEY_2;
	case KeyboardKeys::KEY_3:
		return GLFW_KEY_3;
	case KeyboardKeys::KEY_4:
		return GLFW_KEY_4;
	case KeyboardKeys::KEY_5:
		return GLFW_KEY_5;
	case KeyboardKeys::KEY_6:
		return GLFW_KEY_6;
	case KeyboardKeys::KEY_7:
		return GLFW_KEY_7;
	case KeyboardKeys::KEY_8:
		return GLFW_KEY_8;
	case KeyboardKeys::KEY_9:
		return GLFW_KEY_9;
	case KeyboardKeys::KEY_F1:
		return GLFW_KEY_F1;
	case KeyboardKeys::KEY_F2:
		return GLFW_KEY_F2;
	case KeyboardKeys::KEY_F3:
		return GLFW_KEY_F3;
	case KeyboardKeys::KEY_F4:
		return GLFW_KEY_F4;
	case KeyboardKeys::KEY_F5:
		return GLFW_KEY_F5;
	case KeyboardKeys::KEY_F6:
		return GLFW_KEY_F6;
	case KeyboardKeys::KEY_F7:
		return GLFW_KEY_F7;
	case KeyboardKeys::KEY_F8:
		return GLFW_KEY_F8;
	case KeyboardKeys::KEY_F9:
		return GLFW_KEY_F9;
	case KeyboardKeys::KEY_F10:
		return GLFW_KEY_F10;
	case KeyboardKeys::KEY_F11:
		return GLFW_KEY_F11;
	case KeyboardKeys::KEY_F12:
		return GLFW_KEY_F12;
    case KeyboardKeys::KEY_LEFT_SHIFT:
		return GLFW_KEY_LEFT_SHIFT;
    case KeyboardKeys::KEY_LEFT_CONTROL:
		return GLFW_KEY_LEFT_CONTROL;
	case KeyboardKeys::KEY_RIGHT_SHIFT:
		return GLFW_KEY_RIGHT_SHIFT;
	case KeyboardKeys::KEY_RIGHT_CONTROL:
		return GLFW_KEY_RIGHT_CONTROL;
    case KeyboardKeys::KEY_LEFT_ALT:
		return GLFW_KEY_LEFT_ALT;
    case KeyboardKeys::KEY_RIGHT_ALT:
		return GLFW_KEY_RIGHT_ALT;
	case KeyboardKeys::KEY_LEFT_SUPER:
		return GLFW_KEY_LEFT_SUPER;
	case KeyboardKeys::KEY_RIGHT_SUPER:
		return GLFW_KEY_RIGHT_SUPER;
	case KeyboardKeys::KEY_TAB:
		return GLFW_KEY_TAB;
	case KeyboardKeys::KEY_CAPS_LOCK:
		return GLFW_KEY_CAPS_LOCK;
	case KeyboardKeys::KEY_BACKSPACE:
		return GLFW_KEY_BACKSPACE;
	case KeyboardKeys::KEY_DELETE:
		return GLFW_KEY_DELETE;
	case KeyboardKeys::KEY_INSERT:
		return GLFW_KEY_INSERT;
	case KeyboardKeys::KEY_HOME:
		return GLFW_KEY_HOME;
	case KeyboardKeys::KEY_END:
		return GLFW_KEY_END;
    case KeyboardKeys::KEY_PAGE_UP:
		return GLFW_KEY_PAGE_UP;
    case KeyboardKeys::KEY_PAGE_DOWN:
		return GLFW_KEY_PAGE_DOWN;
	case KeyboardKeys::KEY_KP_0:
		return GLFW_KEY_KP_0;
	case KeyboardKeys::KEY_KP_1:
		return GLFW_KEY_KP_1;
	case KeyboardKeys::KEY_KP_2:
		return GLFW_KEY_KP_2;
	case KeyboardKeys::KEY_KP_3:
		return GLFW_KEY_KP_3;
	case KeyboardKeys::KEY_KP_4:
		return GLFW_KEY_KP_4;
	case KeyboardKeys::KEY_KP_5:
		return GLFW_KEY_KP_5;
	case KeyboardKeys::KEY_KP_6:
		return GLFW_KEY_KP_6;
	case KeyboardKeys::KEY_KP_7:
		return GLFW_KEY_KP_7;
	case KeyboardKeys::KEY_KP_8:
		return GLFW_KEY_KP_8;
	case KeyboardKeys::KEY_KP_9:
		return GLFW_KEY_KP_9;
	case KeyboardKeys::KEY_KP_DECIMAL:
		return GLFW_KEY_KP_DECIMAL;
	case KeyboardKeys::KEY_KP_DIVIDE:
		return GLFW_KEY_KP_DIVIDE;
	case KeyboardKeys::KEY_KP_MULTIPLY:
		return GLFW_KEY_KP_MULTIPLY;
	case KeyboardKeys::KEY_KP_SUBTRACT:
		return GLFW_KEY_KP_SUBTRACT;
	case KeyboardKeys::KEY_KP_ADD:
		return GLFW_KEY_KP_ADD;
	case KeyboardKeys::KEY_KP_ENTER:
		return GLFW_KEY_KP_ENTER;
	case KeyboardKeys::KEY_KP_EQUAL:
		return GLFW_KEY_KP_EQUAL;
	case KeyboardKeys::KEY_NUM_LOCK:
		return GLFW_KEY_NUM_LOCK;
    case KeyboardKeys::KEY_PRINT_SCREEN:
		return GLFW_KEY_PRINT_SCREEN;
    case KeyboardKeys::KEY_SCROLL_LOCK:
		return GLFW_KEY_SCROLL_LOCK;
	case KeyboardKeys::KEY_PAUSE:
		return GLFW_KEY_PAUSE;  
	case KeyboardKeys::KEY_MENU:
		return GLFW_KEY_MENU;
    case KeyboardKeys::KEY_LEFT_BRACKET:
		return GLFW_KEY_LEFT_BRACKET;
    case KeyboardKeys::KEY_RIGHT_BRACKET:
		return GLFW_KEY_RIGHT_BRACKET;
    case KeyboardKeys::KEY_SEMICOLON:
		return GLFW_KEY_SEMICOLON;
	case KeyboardKeys::KEY_APOSTROPHE:
		return GLFW_KEY_APOSTROPHE;
    case KeyboardKeys::KEY_COMMA:
		return GLFW_KEY_COMMA;
    case KeyboardKeys::KEY_PERIOD:
		return GLFW_KEY_PERIOD;
    case KeyboardKeys::KEY_SLASH:
		return GLFW_KEY_SLASH;
    case KeyboardKeys::KEY_BACKSLASH:
		return GLFW_KEY_BACKSLASH;
	case KeyboardKeys::KEY_MINUS:
		return GLFW_KEY_MINUS;
	case KeyboardKeys::KEY_EQUAL:
		return GLFW_KEY_EQUAL;
    case KeyboardKeys::KEY_GRAVE_ACCENT:
		return GLFW_KEY_GRAVE_ACCENT;
	case KeyboardKeys::KEY_WORLD_1:
		return GLFW_KEY_WORLD_1;
	case KeyboardKeys::KEY_WORLD_2:
		return GLFW_KEY_WORLD_2;
	default:
		ELOG_ERROR("Key ", (int)key, " not found in GLFW key map");
		return -1;
	}
}

#endif // INPUT_BACKEND_GLFW_SUPPORT