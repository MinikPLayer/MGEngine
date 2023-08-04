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

Engine::Engine() {
	render.init();
	auto mainCamera = Camera::CreateDefault();
	GameObject::Instantiate(mainCamera);
	Camera::SetMainCamera(mainCamera);
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
