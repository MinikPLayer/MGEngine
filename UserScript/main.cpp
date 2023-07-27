#include <Engine.h>
#include <GameObject.h>
#include <Log.h>

class TestGameObject : public GameObject {
public:
	void Start() override {
		LOG_INFO("TestGameObject::Start()");
	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}