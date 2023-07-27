#include <Engine.h>
#include <GameObject.h>
#include <Log.h>

class TestGameObject : public GameObject {
	std::shared_ptr<GameObject> spawnedChild = nullptr;
	int counter = 0;

	bool original = false;
public:
	void OnDestroy() override {
		LOG_INFO("TestGameObject destroyed - ", counter);
	}

	void Start() override {
		LOG_INFO("TestGameObject::Start() - ", counter);
	}

	void Update() {
		if (!original)
			return;

		if (spawnedChild != nullptr) {
			Destroy(spawnedChild);
		}

		spawnedChild = Instantiate(new TestGameObject(false, ++counter));
	}

	TestGameObject(bool original = true, int counter = 0) {
		this->original = original;
		this->counter = counter;
	}
};

int main() {
	Engine engine;

	GameObject::Instantiate(new TestGameObject());
	engine.run();
}