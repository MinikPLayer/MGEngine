#include "Engine.h"
#include <iostream>
#include "GameObject.h"

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

Engine::Engine() : render(input) {
	render.init();
}


void Engine::run() {
	checkConfiguration();

	GameObject::__RunStart();
	while (render.events()) {
		GameObject::__RunEvents();
		render.clear();
		render.draw();
	}
}
