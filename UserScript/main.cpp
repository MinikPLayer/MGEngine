#include <Engine.h>
#include <GameObject.h>
#include <Log.h>
#include <Mesh.h>

class TestGameObject : public GameObject {
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
		AddComponent(new Mesh(vertices, indices));
	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}