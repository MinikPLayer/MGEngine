#pragma once
#include "Config.h"
#include "Log.h"

#if USE_GL
#include "GLRenderer.h"
#include "GLFWInput.h"
#endif

class Engine {
	void check_configuration();

#if USE_GL
	GLRenderer render;
#endif

	GLFWInput input;
public:
	Engine();
	void run();
};

