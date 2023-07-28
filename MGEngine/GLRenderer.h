#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"
#include "Mesh.h"

class GLRenderer {
	GLFWwindow* window = nullptr;

	GLFWInput& inputSystem;

	// TODO: Move shader to the mesh
	GLuint basicShaderProgram = 0;
	void createDefaultShader();
public:
	GLRenderer(const GLRenderer&) = delete;
	GLRenderer& operator=(const GLRenderer&) = delete;

	GLRenderer(GLFWInput& inputSystem) : inputSystem(inputSystem) {};
	~GLRenderer();

	void clear();

	// Returns if the window should close
	bool events();
	void draw(std::vector<std::weak_ptr<Mesh>> meshes);
	void close();

	void init();
};

