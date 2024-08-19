#ifdef INPUT_BACKEND_GLFW_SUPPORT

#include "GLFWInput.hpp"

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	GLFWInput::__SetScroll(xoffset, yoffset);
}

void GLFWInput::init(GLFWwindow* window) {
	glfwSetScrollCallback(window, mouse_scroll_callback);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	lastMousePos = Vector2<float>((float)xpos, (float)ypos);

	isInitialized = true;
}

int GLFWInput::curMappingId = 0;
std::map<int, InputMapping> GLFWInput::idMappings;
std::map<std::string, int> GLFWInput::nameToIdMappings;
Vector2<float> GLFWInput::lastMousePos = Vector2<float>(0, 0);
float GLFWInput::scrollDeltaX = 0;
float GLFWInput::scrollDeltaY = 0;

bool GLFWInput::isInitialized = false;
CursorModes GLFWInput::cursorMode = CursorModes::Normal;

#endif // INPUT_BACKEND_GLFW_SUPPORT