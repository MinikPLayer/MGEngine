#include "TestObject.hpp"
#include <Input.hpp>
#include <Engine.hpp>
#include <TimeUtils.hpp>
#include <GLTexture.hpp>
#include "Input.hpp"



void TestObject::loadTestObject() {
	auto object = std::make_shared<Model>("assets/user/cube_diorama.fbx");
	add_component(object);
}

void TestObject::start() {
	auto renderer = Engine::get_renderer();
	auto size = renderer.lock()->get_main_screen_resolution();
	renderer.lock()->set_resolution(size / 2);
	renderer.lock()->set_vertical_sync(true);

	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	GLFWInput::SetCursorMode(CursorModes::Disabled);

	loadTestObject();
}

void TestObject::update() {
	if (GLFWInput::key_is_pressed(Keyboard::KEY_H)) {
		GameObject::PrintObjectsHierarchy();
	}
	

	if (GLFWInput::key_is_pressed(Keyboard::KEY_V)) {
		Engine::get_renderer().lock()->set_vertical_sync(true);
	}

	if (GLFWInput::key_is_pressed(Keyboard::KEY_B)) {
		Engine::get_renderer().lock()->set_vertical_sync(false);
	}

	if (GLFWInput::key_is_pressed(Keyboard::ESCAPE)) {
		Engine::stop();
	}
}
