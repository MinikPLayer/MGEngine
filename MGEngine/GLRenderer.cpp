#include "GLRenderer.h"
#include "Log.h"
#include "ErrorCodes.h"
#include "Camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

const char* basicVertexShaderSource = ""
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* basicFragmentShaderSource = ""
"#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void GLRenderer::createDefaultShader() {
	auto vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &basicVertexShaderSource, nullptr);
	glCompileShader(vShader);
	// Check compilation status
	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
		ELOG_FATAL("Vertex shader compilation failed: {}", infoLog);
		exit(2);
	}

	auto fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &basicFragmentShaderSource, nullptr);
	glCompileShader(fShader);
	// Check compilation status
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
		ELOG_FATAL("Fragment shader compilation failed: {}", infoLog);
		exit(3);
	}

	this->basicShaderProgram = glCreateProgram();
	glAttachShader(this->basicShaderProgram, vShader);
	glAttachShader(this->basicShaderProgram, fShader);
	glLinkProgram(this->basicShaderProgram);
	// Check linking status
	glGetProgramiv(this->basicShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->basicShaderProgram, 512, nullptr, infoLog);
		ELOG_FATAL("Shader program linking failed: {}", infoLog);
		exit(4);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
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
	glUseProgram(basicShaderProgram);
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

	createDefaultShader();
	ELOG_INFO("OpenGL renderer initialized");
}
