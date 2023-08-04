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

void Engine::check_configuration() {
#if USE_GL
	ELOG_INFO("Using OpenGL renderer");
#endif
}

Engine::Engine() : render(input) {
	render.init();
	auto mainCamera = Camera::create_default();
	GameObject::Instantiate(mainCamera);
	Camera::set_main_camera(mainCamera);
}

void Engine::run() {
	check_configuration();

	GameObject::__RunStart();
	while (render.events()) {
		Time::__Update();
		GameObject::__RunEvents();
		render.clear();
		render.draw(Mesh::__meshes);
	}
}
