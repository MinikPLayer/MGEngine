#include <Engine.hpp>

#include "TestObject.hpp"

int main() {
	Engine::init();
	GameObject::Instantiate(new TestObject());
	Engine::run();
}