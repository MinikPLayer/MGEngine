#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"
#include "GL_DebugLayers.h"
#include "GLFramebuffer.h"
#include "Config.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	auto glRenderer = static_cast<GLRenderer*>(glfwGetWindowUserPointer(window));
	glRenderer->set_window_size(Vector2<int>(width, height));
}

void GLRenderer::init_shaders() {
	if (!basicShaderProgram->load("assets/engine/mainShader.vert", "assets/engine/mainShader.frag")) {
		ELOG_FATAL("Cannot compile the basic shader program.");
		exit(1);
	}
}

Vector2<int> GLRenderer::get_window_size() {
	return Vector2<int>(windowWidth, windowHeight);
}

void GLRenderer::_set_window_size_internal_(Vector2<int> size) {
	windowWidth = size.x;
	windowHeight = size.y;

	glfwSetWindowSize(window, windowWidth, windowHeight);
}

std::shared_ptr<IFramebuffer> GLRenderer::create_framebuffer(IFramebuffer::AttachmentTypes attachments, bool resize_with_window, Vector2<int> current_size) {
	GLFramebuffer* new_fb = new GLFramebuffer();
	new_fb->init(attachments, resize_with_window, current_size);
	
	return std::shared_ptr<IFramebuffer>(new_fb);
}

GLRenderer::~GLRenderer() {
	glfwTerminate();
	window = nullptr;
}

void GLRenderer::clear_screen() {
	auto clearColor = Camera::GetMainCamera()->get_clear_color();

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GLRenderer::poll_events() {
	glfwPollEvents();
	Input::__Update(window);
	return !glfwWindowShouldClose(window);
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

	//basicShaderProgram->use();
	//basicShaderProgram->set_uniform_mat4f(basicShaderProgram->modelUniformLocation, glm::mat4(1.0f)); // Model identity
	//basicShaderProgram->set_uniform_mat4f(basicShaderProgram->vpUniformLocation, Camera::GetMainCamera()->get_VP_matrix(windowWidth / (float)windowHeight)); // VP identity

	//for (auto mesh : meshes) {
	//	mesh->draw(basicShaderProgram);
	//}

	auto cameraVPMatrix = Camera::GetMainCamera()->get_VP_matrix(windowWidth / (float)windowHeight);
	for (auto smap : shaderMeshMap) {
		auto shader = smap.first;
		shader->use();
		shader->set_uniform_mat4f(basicShaderProgram->modelUniformLocation, glm::mat4(1.0f)); // Model identity
		shader->set_uniform_mat4f(basicShaderProgram->vpUniformLocation, cameraVPMatrix); // VP identity

		for (auto mesh : smap.second) {
			mesh->draw(shader);
		}
	}

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

	init_shaders();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_DEPTH_TEST);

#if USE_GL_DEBUG
	GLDebugLayers::Register();
#endif
	ELOG_INFO("OpenGL renderer initialized");
}
