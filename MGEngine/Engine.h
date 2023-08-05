#pragma once
#include "Config.h"
#include "Log.h"

#if USE_GL
#include "GLRenderer.h"
#include "GLFWInput.h"
#endif

class Engine {
	static void Check_configuration();

#if USE_GL
	static GLRenderer render;
#endif

	static Input input;

	static bool stopped;
public:
	static void Stop();

	static void Init();
	static void Run();
};

