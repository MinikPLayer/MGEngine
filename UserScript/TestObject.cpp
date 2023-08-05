#include "TestObject.h"
#include <Input.h>
#include <Engine.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

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
	mesh->transform.set_scale(Vector3<float>(2.0f, 1.0f, 1.0f));
	mesh->transform.set_position(Vector3<float>(0.0f, 0.0f, 2.0f));

	exitMapping = Input::register_mapping(InputMapping("Exit", Keyboard::ESCAPE));

	Input::SetCursorMode(CursorModes::Disabled);
}

void TestObject::update() {
	mesh->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, sin(Time::ElapsedTime()) * (float)M_PI_2, 0)));
	if (Input::get(exitMapping).value().is_pressed()) {
		Engine::Stop();
	}
}
