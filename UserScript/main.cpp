#include <Engine.hpp>
#include <GameObject.hpp>
#include <Log.hpp>
#include <Mesh.hpp>
#include <TimeUtils.hpp>

#include "Camera.hpp"
#include "TestObject.hpp"
#include "IRenderer.hpp"

int main() {
	Engine::init();
	GameObject::Instantiate(new TestObject());

	auto render = Engine::get_renderer();
	render.lock()->set_window_size(Vector2<int>(1280, 720));
	Engine::run();
}