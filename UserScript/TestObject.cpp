#include "TestObject.hpp"
#include <Input.hpp>
#include <Engine.hpp>
#include <TimeUtils.hpp>
#include <Renderer/GL/GLTexture.hpp>

void TestObject::start() {
	auto renderer = Engine::get_renderer();
	auto size = renderer.lock()->get_main_screen_resolution();
	renderer.lock()->set_resolution(size / 2);
	renderer.lock()->set_vertical_sync(true);

	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	Input::SetCursorMode(CursorModes::Disabled);

	auto textureShader = std::make_shared<GLShader>();
	textureShader->load("engine://shaders/mainShader.vert", "engine://shaders/mainShader_texture.frag");
	textureShader->bind();
	// textureShader->set_uniform_1i(3, 1);

	testTexture = std::make_shared<GLTexture>();
	testTexture->loadFromFile("user://Backpack/1001_albedo.jpg");
	testTexture->bind(0);
	textureShader->set_uniform_1i(3, 0);

	testMaterial = std::make_shared<Material>(textureShader);
	auto cubes = std::make_shared<Model>("user://Backpack/Survival_BackPack_2.fbx", testMaterial);
	add_component(cubes);	

	cubes->lateStartEvent += [](GameObject* obj) {
		LOG_INFO("Late start event called for ", obj->get_type_name());
		obj->get_transform().set_local_scale(Vector3(1.0f, 1.0f, 1.0f) * 0.01f);
	};
}

void TestObject::update() {
	auto prop = testMaterial->get_property("brightness");
	prop.lock()->set_float(sin(Time::ElapsedTime()) * 0.5f + 0.5f);

	testTexture->bind(0);

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
