#include "TestObject.h"
#include <Input.h>
#include <Engine.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

void TestObject::start() {
	LOG_INFO("TestGameObject::Start()");
	Engine::get_renderer().lock()->set_window_title("Hello MGEngine!");

	std::vector<Vertex> vertices = {
		Vertex(0.5f, 0.5f),
		Vertex(0.5f, -0.5f),
		Vertex(-0.5f, -0.5f),
		Vertex(-0.5f, 0.5f)
	};
	std::vector<unsigned int> indices = {
		0, 1, 3, 1, 2, 3
	};
	mesh = std::shared_ptr<Mesh>(new Mesh(vertices, indices));
	add_component(mesh);
	mesh->transform.set_local_scale(Vector3<float>(5.0f, 3.0f, 2.0f));
	mesh->transform.set_position(Vector3<float>(0.0f, 0.0f, 2.0f));

	exitMapping = Input::register_mapping(InputMapping("Exit", Keyboard::ESCAPE));
	smallWindowMapping = Input::register_mapping(InputMapping("Small Window", Keyboard::KEY_1));
	mediumWindowMapping = Input::register_mapping(InputMapping("Medium Window", Keyboard::KEY_2));
	largeWindowMapping = Input::register_mapping(InputMapping("Large Window", Keyboard::KEY_3));
	veryLargeWindowMapping = Input::register_mapping(InputMapping("Very Large Window", Keyboard::KEY_4));

	Input::SetCursorMode(CursorModes::Disabled);

	auto testShader = new GLShader();
	if (!testShader->load("assets/engine/mainShader.vert", "assets/engine/testShader.frag")) {
		LOG_FATAL("Cannot load test shader");
		Engine::stop();
		return;
	}

	auto m = new Model("assets/user/cube.fbx", std::shared_ptr<GLShader>(testShader));
	model = mesh->add_component(m);
	model->transform.set_local_position(Vector3<float>(5.0f, 0.0f, 0.0f));
	model->transform.set_local_scale(Vector3<float>(1.0f, 1.0f, 0.5f));

	mesh->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(1.2f, 0.5f, 0.25f)));
	LOG_DEBUG("Model transform: ", model->transform.to_string());
}

void TestObject::update() {
	mesh->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, sin(Time::ElapsedTime()) * (float)M_PI_2, 0)));
	model->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, Time::ElapsedTime(), 0)));

	if (Input::key_is_pressed(Keyboard::KEY_V)) {
		Engine::get_renderer().lock()->set_vertical_sync(true);
	}

	if (Input::key_is_pressed(Keyboard::KEY_B)) {
		Engine::get_renderer().lock()->set_vertical_sync(false);
	}

	if (Input::get(exitMapping).value().is_pressed()) {
		Engine::stop();
	}

	if (Input::get(smallWindowMapping).value().is_just_pressed()) {
		Engine::get_renderer().lock()->set_window_size(Vector2<int>(800, 600));
	}

	if (Input::get(mediumWindowMapping).value().is_just_pressed()) {
		Engine::get_renderer().lock()->set_window_size(Vector2<int>(1280, 820));
	}

	if (Input::get(largeWindowMapping).value().is_just_pressed()) {
		Engine::get_renderer().lock()->set_window_size(Vector2<int>(1920, 1080));
	}

	if (Input::get(veryLargeWindowMapping).value().is_just_pressed()) {
		Engine::get_renderer().lock()->set_window_size(Vector2<int>(3000, 1800));
	}
}
