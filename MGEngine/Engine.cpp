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

std::weak_ptr<IRenderer> Engine::get_renderer() {
	return render;
}

void Engine::stop() {
	stopped = true;
}

void Engine::init() {
	render->init();
	auto mainCamera = Camera::CreateDefault();
	GameObject::Instantiate(mainCamera);
	Camera::SetMainCamera(mainCamera);
}

void Engine::run() {
	check_configuration();

	GameObject::__RunStart();
	while (render->poll_events() && !stopped) {
		Time::__Update();
		GameObject::__RunEvents();
		render->clear_screen();
		render->draw(Mesh::__meshes);
	}
}

#if USE_GL
std::shared_ptr<IRenderer> Engine::render = std::shared_ptr<IRenderer>(new GLRenderer());
#endif // USE_GL

Input Engine::input;
bool Engine::stopped;