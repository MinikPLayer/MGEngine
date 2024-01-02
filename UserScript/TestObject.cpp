#include "TestObject.hpp"
#include <Input.hpp>
#include <Engine.hpp>
#include <TimeUtils.hpp>
#include <GLTexture.hpp>

void TestObject::start() {
	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	Input::SetCursorMode(CursorModes::Disabled);

	auto textureShader = std::make_shared<GLShader>();
	textureShader->load("assets/engine/mainShader.vert", "assets/engine/mainShader_texture.frag");
	textureShader->bind();
	textureShader->set_uniform_1i(3, 1);

	testTexture = std::make_shared<GLTexture>();
	testTexture->loadFromFile("assets/user/Backpack/1001_albedo.jpg");
	testTexture->bind(1);

	auto cubes = std::make_shared<Model>("assets/user/Backpack/Survival_BackPack_2.fbx", textureShader);
	add_component(cubes);	

	//cubes = std::make_shared<Model>("assets/user/cube.fbx");
	//cubes->get_transform().set_position(Vector3(3.0f, 0.0f, 0.0f));
	//add_component(cubes);

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
