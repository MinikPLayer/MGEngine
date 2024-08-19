#pragma once

#include "Log.hpp"

#ifdef RENDER_BACKEND_OGL_SUPPORT
#include "GLRenderer.hpp"
#include "GLFWInput.hpp"
#endif

#ifdef INPUT_BACKEND_GLFW_SUPPORT
#include "GLFWInput.hpp"
#endif

class Engine {
	static void check_configuration();

	static std::shared_ptr<IRenderer> render;

	static GLFWInput input;

	static bool stopped;
public:
	static std::weak_ptr<IRenderer> get_renderer();

	static void stop();

	static void init();
	static void run();
};

