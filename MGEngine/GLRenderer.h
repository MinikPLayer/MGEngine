#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"

class GLRenderer {
	GLFWwindow* window = nullptr;

	GLFWInput& inputSystem;
public:
	GLRenderer(const GLRenderer&) = delete;
	GLRenderer& operator=(const GLRenderer&) = delete;

	GLRenderer(GLFWInput& inputSystem) : inputSystem(inputSystem) {};
	~GLRenderer();

	void clear();

	// Returns if the window should close
	bool events();
	void draw();
	void close();

	void init();
};

