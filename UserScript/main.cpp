#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>
#include <TimeUtils.h>

#include "Camera.h"

class TestGameObject : public GameObject {
	std::shared_ptr<Mesh> mesh;
public:
	void Start() override {
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
		AddComponent(mesh);
		this->transform.setLocalScale(Vector3<float>(2.0f, 1.0f, 1.0f));
		mesh->transform.setScale(Vector3<float>(2.0f, 1.0f, 1.0f));
		mesh->transform.setPosition(Vector3<float>(0.0f, 0.0f, 2.0f));
	}

	void Update() override {
		// auto position = mesh->transform.getLocalPosition();
		// position.x = cos(Time::elapsedTime());
		// position.y = sin(Time::elapsedTime());
		// mesh->transform.setLocalPosition(position);

		// mesh->transform.setLocalRotation(Quaternion::from_euler(Vector3<float>(0, Time::elapsedTime(), 0)));

		auto camera = Camera::getMainCamera();
		camera->transform.setLocalRotation(Quaternion::from_euler(Vector3<float>(0, sin(Time::elapsedTime()) / 2.f, 0)));

	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}