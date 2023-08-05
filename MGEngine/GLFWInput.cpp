#include "GLFWInput.h"

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Input::__set_scroll(xoffset, yoffset);
}

void Input::init(GLFWwindow* window) {
	glfwSetScrollCallback(window, mouse_scroll_callback);

	isInitialized = true;
}

int Input::curMappingId = 0;
std::map<int, InputMapping> Input::idMappings;
std::map<std::string, int> Input::nameToIdMappings;
Vector2<float> Input::lastMousePos = Vector2<float>(0, 0);
float Input::scrollDeltaX = 0;
float Input::scrollDeltaY = 0;

bool Input::isInitialized = false;