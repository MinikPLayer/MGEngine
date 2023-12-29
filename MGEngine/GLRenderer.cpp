#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"
#include "GL_DebugLayers.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	auto glRenderer = static_cast<GLRenderer*>(glfwGetWindowUserPointer(window));
	glRenderer->set_window_size(Vector2<int>(width, height));
}

void GLRenderer::init_shaders() {
	if (!basicShaderProgram.load("assets/engine/mainShader.vert", "assets/engine/mainShader.frag")) {
		ELOG_FATAL("Cannot compile the basic shader program.");
		exit(1);
	}
}

Vector2<int> GLRenderer::get_window_size() {
	return Vector2<int>(windowWidth, windowHeight);
}

void GLRenderer::set_window_size(Vector2<int> size) {
	windowWidth = size.x;
	windowHeight = size.y;

	glfwSetWindowSize(window, windowWidth, windowHeight);
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

void GLRenderer::draw(std::vector<std::weak_ptr<Mesh>> meshes) {
	basicShaderProgram.use();
	basicShaderProgram.set_uniform_mat4f(basicShaderProgram.modelUniformLocation, glm::mat4(1.0f)); // Model identity
	basicShaderProgram.set_uniform_mat4f(basicShaderProgram.vpUniformLocation, Camera::GetMainCamera()->get_VP_matrix(windowWidth / (float)windowHeight)); // VP identity

	for (auto mesh : meshes) {
		mesh.lock()->draw(basicShaderProgram);
	}
	glfwSwapBuffers(window);
}

void GLRenderer::shutdown() {
	glfwSetWindowShouldClose(window, true);
}

void GLRenderer::init(Vector2<int> size) {
	ELOG_INFO("Initializing OpenGL renderer");
	if (size.x == 0 || size.y == 0) {
		ELOG_INFO("No size provided, using default: ", 800, "x", 600);
		size.x = 800;
		size.y = 600;
	}
	else {
		ELOG_INFO("Using window size: ", size.x, "x", size.y);
		windowWidth = size.x;
		windowHeight = size.y;
	}

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
