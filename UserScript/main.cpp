#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>
#include <TimeUtils.h>
#include <corecrt_math_defines.h>

#include "Camera.h"

class TestGameObject : public GameObject {
	std::shared_ptr<Mesh> mesh;

	int exitMapping = -1;
public:
	void start() override {
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

	void update() override {
		// auto position = mesh->transform.getLocalPosition();
		// position.x = cos(Time::elapsedTime());
		// position.y = sin(Time::elapsedTime());
		// mesh->transform.setLocalPosition(position);

		// mesh->transform.setLocalRotation(Quaternion::from_euler(Vector3<float>(0, Time::elapsedTime(), 0)));

		mesh->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0, sin(Time::ElapsedTime()) * M_PI_2, 0)));
		if (Input::get(exitMapping).value().is_pressed()) {
			Engine::Stop();
		}
	}
};

int main() {
	Engine::Init();
	GameObject::Instantiate(new TestGameObject());
	Engine::Run();
}