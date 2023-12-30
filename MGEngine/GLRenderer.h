#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWInput.h"
#include "Mesh.h"
#include "GLShader.h"
#include "IRenderer.h"

// TODO: Move Renderer to interface
class GLRenderer : public IRenderer {
	GLFWwindow* window = nullptr;

	// TODO: Move shader to the mesh
	// GLShader basicShaderProgram;
	std::shared_ptr<GLShader> basicShaderProgram = std::shared_ptr<GLShader>(new GLShader());
	void init_shaders();

	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;

protected:

	std::shared_ptr<IFramebuffer> _create_main_framebuffer_() override;
	void _init_internal_(Vector2<int> size = Vector2<int>(0, 0)) override;
	void _set_window_size_internal_(Vector2<int> size) override;
public:
	std::shared_ptr<IFramebuffer> create_framebuffer(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) override;

	Vector2<int> get_window_size() override;

	GLRenderer(const GLRenderer&) = delete;
	GLRenderer& operator=(const GLRenderer&) = delete;

	GLRenderer() {};
	~GLRenderer();

	void clear_screen() override;

	// Returns if the window should close
	bool poll_events() override;
	void draw(std::vector<std::shared_ptr<Mesh>> meshes) override;
	void shutdown() override;
};

