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
	}


	void Update() override {
		auto position = mesh->transform.getPosition();
		position.y = sin(Time::elapsedTime());
		mesh->transform.setPosition(position);
	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}