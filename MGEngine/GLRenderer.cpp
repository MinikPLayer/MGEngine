#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"
#include "GL_DebugLayers.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GLRenderer::initShaders() {
	if (!basicShaderProgram.load("assets/mainShader.vert", "assets/mainShader.frag")) {
		ELOG_FATAL("Cannot compile the basic shader program.");
		exit(1);
	}
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

void GLRenderer::draw(std::vector<std::weak_ptr<Mesh>> meshes) {
	basicShaderProgram.use();
	basicShaderProgram.setUniformMat4f(0, glm::mat4(1.0f)); // Model identity
	basicShaderProgram.setUniformMat4f(1, glm::mat4(1.0f)); // VP identity

	for (auto mesh : meshes) {
		mesh.lock()->draw();
	}
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

#if USE_GL_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

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

	initShaders();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

#if USE_GL_DEBUG
	GLDebugLayers::Register();
#endif
	ELOG_INFO("OpenGL renderer initialized");
}
