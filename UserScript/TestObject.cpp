#include "TestObject.hpp"
#include <Input.hpp>
#include <Engine.hpp>
#include <TimeUtils.hpp>
#include <GLTexture.hpp>
#include "Input.hpp"



void TestObject::loadTestObject() {
	texture = std::make_shared<GLTexture>();
	texture->loadFromFile("assets/user/Backpack/1001_albedo.jpg");
	texture->bind(0);
	auto textureShader = IShader::create("assets/engine/mainShader.vert", "assets/engine/mainShader_texture.frag");
	testMaterial = Material::create(textureShader);

	auto object = std::make_shared<Model>("assets/user/Backpack/Survival_BackPack_2.fbx", testMaterial);
	add_component(object);
}

void TestObject::start() {
	auto renderer = Engine::get_renderer();
	auto size = renderer.lock()->get_main_screen_resolution();
	renderer.lock()->set_resolution(size / 2);
	renderer.lock()->set_vertical_sync(true);

	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");
	Input::set_cursor_mode(CursorModes::Disabled);

	loadTestObject();
}

void TestObject::update() {
	texture->bind(0);

	if (Input::is_key_pressed(KeyboardKeys::KEY_H)) {
		GameObject::PrintObjectsHierarchy();
	}
	

	if (Input::is_key_pressed(KeyboardKeys::KEY_V)) {
		Engine::get_renderer().lock()->set_vertical_sync(true);
	}

	if (Input::is_key_pressed(KeyboardKeys::KEY_B)) {
		Engine::get_renderer().lock()->set_vertical_sync(false);
	}

	if (Input::is_key_pressed(KeyboardKeys::KEY_ESCAPE)) {
		Engine::stop();
	}
}
