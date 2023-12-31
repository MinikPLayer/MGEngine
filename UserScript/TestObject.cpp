#include "TestObject.h"
#include <Input.h>
#include <Engine.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

void test_fullscreen_quad(TestObject& to) {
	//auto renderer = Engine::get_renderer().lock();
	//auto fbo = renderer->create_framebuffer(IFramebuffer::AttachmentTypes::COLOR_DEPTH_STENCIL, true);
	//renderer->add_framebuffer(fbo);

	//std::vector<Vertex> vertices = {
	//	Vertex(-1.0f, -1.0f, 0.0f, 0, 0, 0, 0.f, 0.f),
	//	Vertex(1.0f, 1.0f, 0.0f,   0, 0, 0, 1.f, 1.f),
	//	Vertex(-1.0f, 1.0f, 0.0f,  0, 0, 0, 0.f, 1.f),
	//	Vertex(1.0f, -1.0f, 0.0f,  0, 0, 0, 1.f, 0.f),
	//};

	//std::vector<unsigned int> indices = {
	//	0, 1, 2, 0, 3, 1
	//};

	//auto newMesh = new Mesh(vertices, indices);
	//
	//auto customShader = new GLShader();
	//customShader->load("assets/engine/fullscreenQuad.vert", "assets/engine/fullscreenQuad.frag");
	//customShader->usingModelMatrices = false;
	//customShader->use();
	//customShader->set_uniform_1i(0, 0);
	//fbo->bind_color_attachment(0);

	//newMesh->set_custom_shader(std::shared_ptr<IShader>(customShader));
	//to.add_component(newMesh);
}

void TestObject::start() {
	LOG_INFO("TestGameObject::Start()");

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

	// test_fullscreen_quad(*this);
}

void TestObject::update() {
	mesh->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, sin(Time::ElapsedTime()) * (float)M_PI_2, 0)));
	model->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, Time::ElapsedTime(), 0)));

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
