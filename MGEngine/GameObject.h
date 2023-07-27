#pragma once
#include "Transform.h"
#include <vector>
#include <memory>
#include "Log.h"

class GameObject {
	std::vector<std::shared_ptr<GameObject>> children;
	std::weak_ptr<GameObject> parent;

	std::weak_ptr<GameObject> self;
	size_t hash = -1;

	static std::vector<std::shared_ptr<GameObject>> __objects;

	bool isStarted = false;
	bool isDestroyed = false;

	void __runEvents() {
#if !NDEBUG
		if (isDestroyed) {
			ELOG_ERROR("Destroyed object is still running events");
		}
#endif

		if (!isStarted) {
			Start();
			isStarted = true;
		}

		Update();

		for (auto c : children) {
			c->__runEvents();
		}
	}
public:

	Transform transform;

	template<typename T>
	static std::shared_ptr<T> Instantiate(std::shared_ptr<T> object, std::shared_ptr<GameObject> parent = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		__objects.push_back(object);

		object->self = object;
		object->hash = typeid(T).hash_code();
		if (parent != nullptr) {
			parent->AddComponent(object);
		}

		return object;
	}

	template<typename T>
	static std::shared_ptr<T> Instantiate(T* object, std::shared_ptr<GameObject> parent = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		auto objPtr = std::shared_ptr<T>(object);
		return Instantiate<T>(objPtr, parent);
	}

	static void Destroy(std::shared_ptr<GameObject> object, bool removeFromObjects = true) {
#if !NDEBUG
		if (object->isDestroyed) {
			ELOG_ERROR("Object destoyed twice");
		}
#endif

		if (!object->parent.expired()) {
			object->parent.lock()->RemoveComponent(object);
		}

		object->OnDestroy();
		object->isDestroyed = true;
		for (auto child : object->children) {
			Destroy(child, false);
		}

		if (removeFromObjects) {
			__objects.erase(std::remove(__objects.begin(), __objects.end(), object), __objects.end());
		}
	}

	static void __RunStart() {
		for (auto obj : __objects) {
			if (!obj->isStarted) {
				obj->Start();
				obj->isStarted = true;
			}

		}
	}

	static void __RunEvents() {
		for (auto obj : __objects) {
			obj->__runEvents();
		}
	}

	template<typename T>
	bool isType() {
		return hash == typeid(T).hash_code();
	}

	virtual void OnDestroy() {}
	virtual void Start() {}
	virtual void Update() {}

	void AddComponent(std::shared_ptr<GameObject> child);
	void RemoveComponent(std::shared_ptr<GameObject> child);

	// Disable copy constructor and assignment operator
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	GameObject() {}
	~GameObject();
};