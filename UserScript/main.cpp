#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>
#include <TimeUtils.h>

#include "Camera.h"
#include "TestObject.h"
#include "IRenderer.h"

int main() {
	Engine::init();
	GameObject::Instantiate(new TestObject());

	auto render = Engine::get_renderer();
	render.lock()->set_window_size(Vector2<int>(1280, 720));
	Engine::run();
}