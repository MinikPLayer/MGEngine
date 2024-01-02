#include "TestObject.h"
#include <Input.h>
#include <Engine.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

void TestObject::start() {
	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	Input::SetCursorMode(CursorModes::Disabled);

	auto cubes = std::make_shared<Model>("assets/user/blender_3.fbx");
	add_component(cubes);

	cubes->lateStartEvent += [](GameObject* obj) {
		LOG_INFO("Late start event called for ", obj->get_type_name());
		obj->get_transform().set_local_scale(Vector3(1.0f, 1.0f, 1.0f) * 0.01f);
	};
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
