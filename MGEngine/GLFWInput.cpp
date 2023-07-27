#include "GLFWInput.h"

void GLFWInput::update(GLFWwindow* window) {
	for (auto pair : this->idMappings) {
		auto mapping = pair.second;
		mapping.update(window);
	}
}
