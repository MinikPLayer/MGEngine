#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"
#include "GL_DebugLayers.h"
#include "GLFramebuffer.h"
#include "Config.h"
#include "Engine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	auto glRenderer = static_cast<GLRenderer*>(glfwGetWindowUserPointer(window));
	glRenderer->set_window_size(Vector2<int>(width, height));
}

void GLRenderer::__init_shaders__() {
	if (!basicShaderProgram->load("assets/engine/mainShader.vert", "assets/engine/mainShader.frag")) {
		ELOG_FATAL("Cannot compile the basic shader program.");
		exit(1);
	}
}

void GLRenderer::__init_postprocess_mesh__() {
	std::vector<Vertex> vertices = {
		Vertex(-1.0f, -1.0f, 0.0f, 0, 0, 0, 0.f, 0.f),
		Vertex(1.0f, 1.0f,  0.0f,  0, 0, 0, 1.f, 1.f),
		Vertex(-1.0f, 1.0f, 0.0f,  0, 0, 0, 0.f, 1.f),
		Vertex(1.0f, -1.0f, 0.0f,  0, 0, 0, 1.f, 0.f),
	};

	std::vector<unsigned int> indices = {
		0, 1, 2, 0, 3, 1
	};

	auto newMesh = new Mesh(vertices, indices);

	ppShader = std::shared_ptr<GLShader>(new GLShader());
	if (!ppShader->load("assets/engine/fullscreenQuad.vert", "assets/engine/fullscreenQuad.frag")) {
		ELOG_FATAL("Cannot load PostProcess shader.");
		Engine::stop();
		return;
	}
	ppShader->usingModelMatrices = false;
	ppShader->bind();
	ppShader->set_uniform_1i(0, 0);

	newMesh->set_custom_shader(ppShader);
	ppMesh = std::unique_ptr<Mesh>(newMesh);
}

Vector2<int> GLRenderer::get_window_size() {
	return Vector2<int>(windowWidth, windowHeight);
}

void GLRenderer::_set_window_size_internal_(Vector2<int> size) {
	windowWidth = size.x;
	windowHeight = size.y;

	glfwSetWindowSize(window, windowWidth, windowHeight);
}

void GLRenderer::set_vertical_sync(bool enabled) {
	glfwSwapInterval(enabled ? 1 : 0);
}

void GLRenderer::set_window_title(std::string title) {
	glfwSetWindowTitle(window, title.c_str());
}

std::shared_ptr<IFramebuffer> GLRenderer::_create_framebuffer_(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) {
	GLFramebuffer* new_fb = new GLFramebuffer();
	new_fb->init(attachments, resize_with_window, current_size);
	
	return std::shared_ptr<IFramebuffer>(new_fb);
}

GLRenderer::~GLRenderer() {
	glfwTerminate();
	window = nullptr;
}

void GLRenderer::clear() {
	auto clearColor = Camera::GetMainCamera()->get_clear_color();

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GLRenderer::poll_events() {
	glfwPollEvents();
	Input::__Update(window);
	return !glfwWindowShouldClose(window);
}

void GLRenderer::__draw_postprocess__() {
	bind_screen_framebuffer();
	clear();

	glDisable(GL_DEPTH_TEST);
	ppShader->bind();
	bind_postprocess_color_texture();
	ppMesh->draw(ppShader);
	glEnable(GL_DEPTH_TEST);
}

void GLRenderer::draw(std::vector<std::shared_ptr<Mesh>> meshes) {
	std::map<std::shared_ptr<GLShader>, std::vector<std::shared_ptr<Mesh>>> shaderMeshMap;
	shaderMeshMap.insert(std::make_pair(basicShaderProgram, std::vector<std::shared_ptr<Mesh>>()));

	for (auto mesh : meshes) {
		if (!mesh->is_custom_shader()) {
			shaderMeshMap[basicShaderProgram].push_back(mesh);
		}
		else {
#if SC_FATAL_ON
			auto shaderPtr = mesh->get_custom_shader();
			if (shaderPtr == nullptr) {
				ELOG_FATAL("Mesh is flagged as using a custom shader, but returns an empty shader.");
				exit(0x1C5D4E); // ! CustomShader Empty
			}

			auto shader = std::dynamic_pointer_cast<GLShader>(shaderPtr);
			if (shader == nullptr) {
				ELOG_FATAL("Mesh is using an incompatible shader type. Using GL Rendering but shader is not a GLShader.");
				exit(0x1C5D41); // ! Custom Shader Incompatible
			}
#else
			auto shader = std::static_pointer_cast<GLShader>(mesh->get_custom_shader());
#endif
			if (!shaderMeshMap.contains(shader)) {
				shaderMeshMap.insert(std::make_pair(shader, std::vector<std::shared_ptr<Mesh>>()));
			}

			shaderMeshMap[shader].push_back(mesh);
		}
	}

	// Bind main drawing framebuffer
	bind_main_draw_framebuffer();
	// bind_screen_framebuffer();
	clear();

	glEnable(GL_DEPTH_TEST);
	auto cameraVPMatrix = Camera::GetMainCamera()->get_VP_matrix(windowWidth / (float)windowHeight);
	for (auto smap : shaderMeshMap) {
		auto shader = smap.first;
		shader->bind();
		if (shader->usingModelMatrices) {
			shader->set_uniform_mat4f(basicShaderProgram->modelUniformLocation, glm::mat4(1.0f)); // Model identity
			shader->set_uniform_mat4f(basicShaderProgram->vpUniformLocation, cameraVPMatrix); // VP identity
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}

		for (auto mesh : smap.second) {
			mesh->draw(shader);
		}

		if (!shader->usingModelMatrices) {
			glEnable(GL_DEPTH_TEST);
		}
	}

	__draw_postprocess__();

	glfwSwapBuffers(window);
}

void GLRenderer::shutdown() {
	glfwSetWindowShouldClose(window, true);
}

std::shared_ptr<IFramebuffer> GLRenderer::_create_main_framebuffer_() {
	GLFramebuffer* new_fb = new GLFramebuffer();
	new_fb->init_as_main();
	return std::shared_ptr<IFramebuffer>(new_fb);
}

void GLRenderer::_init_internal_(Vector2<int> size) {
	ELOG_INFO("Initializing OpenGL renderer");
	ELOG_INFO("Using window size: ", size.x, "x", size.y);
	windowWidth = size.x;
	windowHeight = size.y;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if USE_GL_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	window = glfwCreateWindow(windowWidth, windowHeight, "MGEngine", nullptr, nullptr);
	if (window == nullptr) {
		ELOG_FATAL("Failed to create GLFW window");
		glfwTerminate();
		exit(ERROR_CODE_GLFW_INIT_FAIL);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		ELOG_FATAL("Failed to initialize GLAD");
		glfwTerminate();
		exit(ERROR_CODE_GLAD_INIT_FAIL);
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// TODO: Add option to disable vsync
	glfwSwapInterval(1);

	__init_shaders__();
	__init_postprocess_mesh__();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_DEPTH_TEST);

#if USE_GL_DEBUG
	GLDebugLayers::Register();
#endif
	ELOG_INFO("OpenGL renderer initialized");
}
