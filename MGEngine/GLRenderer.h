#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"
#include "Mesh.h"
#include "GLShader.h"

class GLRenderer {
	GLFWwindow* window = nullptr;

	// TODO: Move shader to the mesh
	Shader basicShaderProgram;
	void init_shaders();

	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;
public:
	void set_window_size(unsigned int width, unsigned int height);

	GLRenderer(const GLRenderer&) = delete;
	GLRenderer& operator=(const GLRenderer&) = delete;

	GLRenderer() {};
	~GLRenderer();

	void clear();

	// Returns if the window should close
	bool events();
	void draw(std::vector<std::weak_ptr<Mesh>> meshes);
	void close();

	void init();
};

