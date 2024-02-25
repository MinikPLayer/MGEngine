#include <Engine.hpp>
#include <GameObject.hpp>
#include <Log.hpp>
#include <Mesh.hpp>
#include <TimeUtils.hpp>

#include "Camera.hpp"
#include "TestObject.hpp"
#include "Renderer/IRenderer.hpp"

int main() {
	Engine::init();
	GameObject::Instantiate(new TestObject());
	Engine::run();
}