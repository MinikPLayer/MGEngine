#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>
#include <TimeUtils.h>

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
		mesh->transform.setScale(Vector3<float>(0.5f, 1.0f, 1.0f));
	}

	void Update() override {
		auto position = mesh->transform.getLocalPosition();
		position.x = cos(Time::elapsedTime());
		position.y = sin(Time::elapsedTime());
		mesh->transform.setLocalPosition(position);
	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}