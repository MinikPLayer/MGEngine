#include "TestObject.h"
#include <Input.h>
#include <Engine.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

void TestObject::start() {
	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	Input::SetCursorMode(CursorModes::Disabled);

	auto cubes = std::make_shared<Model>("assets/user/test_relation_cubes.fbx");
	// auto cubes = std::make_shared<Model>("assets/user/cube.fbx");
	add_component(cubes);
}

void TestObject::update() {
	if (Input::key_is_pressed(Keyboard::KEY_H)) {
		GameObject::PrintObjectsHierarchy();
	}
	

	if (Input::key_is_pressed(Keyboard::KEY_V)) {
		Engine::get_renderer().lock()->set_vertical_sync(true);
	}

	if (Input::key_is_pressed(Keyboard::KEY_B)) {
		Engine::get_renderer().lock()->set_vertical_sync(false);
	}

	if (Input::key_is_pressed(Keyboard::ESCAPE)) {
		Engine::stop();
	}
}
