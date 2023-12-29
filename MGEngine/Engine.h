#pragma once
#include "Config.h"
#include "Log.h"

#if USE_GL
#include "GLRenderer.h"
#include "GLFWInput.h"
#endif

class Engine {
	static void check_configuration();

	static std::shared_ptr<IRenderer> render;

	static Input input;

	static bool stopped;
public:
	static std::weak_ptr<IRenderer> get_renderer();

	static void stop();

	static void init();
	static void run();
};

