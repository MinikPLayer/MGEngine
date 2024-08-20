#pragma once

#if RENDER_BACKEND_OGL_SUPPORT
#include "GLInclude.hpp"

#if NDEBUG
#define USE_GL_DEBUG 0
#else
#define USE_GL_DEBUG 1
#endif

#include <GLFW/glfw3.h>
#include "GLFWInput.hpp"
#include "Mesh.hpp"
#include "GLShader.hpp"
#include "IRenderer.hpp"

// TODO: Add more logs
class GLRenderer : public IRenderer {
	std::shared_ptr<GLFWwindow> window = nullptr;

	// PostProcess mesh
	std::unique_ptr<Mesh> ppMesh = nullptr;
	std::shared_ptr<GLShader> ppShader = nullptr;
	std::shared_ptr<Material> ppMaterial = nullptr;

	//std::shared_ptr<GLShader> basicShaderProgram = std::shared_ptr<GLShader>(new GLShader());
	std::shared_ptr<Material> basicMaterial = std::shared_ptr<Material>(Material::create(std::shared_ptr<GLShader>(new GLShader())));

	void __init_shaders__();
	void __init_postprocess_mesh__();

	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;

	void __draw_postprocess__();

protected:

	std::shared_ptr<IFramebuffer> _create_framebuffer_(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) override;
	std::shared_ptr<IFramebuffer> _create_main_framebuffer_() override;
	void _init_internal_(Vector2<int> size = Vector2<int>(0, 0)) override;
	void _set_window_size_internal_(Vector2<int> size) override;
	std::shared_ptr<IShader> _create_default_shader_() override;
	std::shared_ptr<IShader> _create_shader_(std::string vertex_shader, std::string fragment_shader) override;

	// Returns true if the window should close
	bool _poll_events_() override;

public:
	RenderBackends get_backend_type() override;

	Vector2<int> get_main_screen_resolution() override;

	void set_vertical_sync(bool enabled) override;
	void set_window_title(std::string title) override;

	Vector2<int> get_resolution() override;

	// TODO: Add generic in the interface
	std::weak_ptr<GLFWwindow> get_gl_window();

	GLRenderer(const GLRenderer&) = delete;
	GLRenderer& operator=(const GLRenderer&) = delete;

	GLRenderer() {};
	~GLRenderer();

	void clear() override;

	void draw(std::vector<std::shared_ptr<Mesh>> meshes) override;
	void shutdown() override;
};

#endif