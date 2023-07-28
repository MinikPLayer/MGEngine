#pragma once

#include <glad/glad.h>
#include <functional>
#include "Log.h"
#include <sstream>
#include <GLFW/glfw3.h>

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei,
	const char* message,
	const void*) {
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::stringstream ss;
	ss << "---------------" << std::endl;
	ss << "Debug message (" << id << "): " << message << std::endl;

	switch (source) {
		case GL_DEBUG_SOURCE_API:             ss << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   ss << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: ss << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     ss << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     ss << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           ss << "Source: Other"; break;
	} ss << std::endl;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:               ss << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ss << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  ss << "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         ss << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         ss << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              ss << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          ss << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           ss << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               ss << "Type: Other"; break;
	} ss << std::endl;

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         ELOG_FATAL(ss.str(), "Severity: high\n"); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       ELOG_ERROR(ss.str(), "Severity: medium\n"); break;
		case GL_DEBUG_SEVERITY_LOW:          ELOG_WARNING(ss.str(), "Severity: low\n"); break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: ELOG_INFO(ss.str(), "Severity: notification\n"); break;
	}
}

class GLDebugLayers {
public:
	static void Register(std::function<void(GLenum, GLenum, unsigned int, GLenum, GLsizei, const char*, const void*)> callback = nullptr) {
#if NDEBUG
		ELOG_WARNING("OpenGL Debug context created in release mode");
#endif
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
			ELOG_INFO("OpenGL Debug context created successfully");
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
		}
		else {
			ELOG_FATAL("Failed to create debug context! Try setting glfwWindowHint GLFW_OPENGL_DEBUG_CONTEXT to true");
		}
	}
};