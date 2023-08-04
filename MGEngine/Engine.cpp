#include "Engine.h"
#include <iostream>
#include "GameObject.h"
#include "Camera.h"
#include "TimeUtils.h"

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
	auto mainCamera = Camera::createDefault();
	GameObject::Instantiate(mainCamera);
	Camera::setMainCamera(mainCamera);
}

void Engine::run() {
	checkConfiguration();

	GameObject::__RunStart();
	while (render.events()) {
		Time::__update();
		GameObject::__RunEvents();
		render.clear();
		render.draw(Mesh::__meshes);
	}
}
