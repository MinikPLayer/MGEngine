#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLRenderer::~GLRenderer() {
	glfwTerminate();
	window = nullptr;
}

void GLRenderer::clear() {
	auto clearColor = Camera::getMainCamera()->getClearColor();

	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GLRenderer::events() {
	glfwPollEvents();
	inputSystem.update(window);
	return !glfwWindowShouldClose(window);
}

void GLRenderer::draw() {
	glfwSwapBuffers(window);
}

void GLRenderer::close() {
	glfwSetWindowShouldClose(window, true);
}

void GLRenderer::init() {
	ELOG_INFO("Initializing OpenGL renderer");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "MGEngine", nullptr, nullptr);
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	ELOG_INFO("OpenGL renderer initialized");
}
