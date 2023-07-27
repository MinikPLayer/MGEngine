#include "Engine.h"
#include <iostream>

#if USE_GL 
#pragma message("[INFO] Using OpenGL renderer")
#else
#error "No renderer selected"
#endif

void Engine::checkConfiguration() {
#if USE_GL
	ELOG_INFO("Using OpenGL renderer");
#endif
}

Engine::Engine() : render(input) {}

void Engine::init() {
	render.init();
}

void Engine::run() {
	checkConfiguration();
	while (render.events()) {
		render.clear();
		render.draw();
	}
}
