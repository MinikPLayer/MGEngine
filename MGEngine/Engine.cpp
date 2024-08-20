#include "Engine.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "Camera.hpp"
#include "TimeUtils.hpp"


void Engine::check_configuration() {}

std::weak_ptr<IRenderer> Engine::get_renderer() {
	return render;
}

void Engine::stop() {
	stopped = true;
}

void Engine::init() {
	// TODO: Load render backend from config or something
#ifdef RENDER_BACKEND_OGL_SUPPORT
	render = std::shared_ptr<IRenderer>(new GLRenderer());
#else
#error "No renderer selected"
#endif

	render->init();

#ifdef RENDER_BACKEND_OGL_SUPPORT
	auto glRenderer = (GLRenderer*)render.get();
	auto backend = new GLFWInputBackend(glRenderer->get_gl_window());
	Input::init(std::unique_ptr<IInputBackend>(backend));
#endif // RENDER_BACKEND_OGL_SUPPORT


	auto mainCamera = Camera::CreateDefault();
	GameObject::Instantiate(mainCamera);
	Camera::SetMainCamera(mainCamera);
}

void Engine::run() {
	check_configuration();

	GameObject::__RunStart__();
	while (render->poll_events() && !stopped) {
		Time::__Update();
		GameObject::__RunUpdate__();
		render->clear_screen();
		render->draw(Mesh::__meshes);
	}
}

std::shared_ptr<IRenderer> Engine::render;
bool Engine::stopped;