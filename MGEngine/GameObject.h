#pragma once
#include "Transform.h"
#include <vector>
#include <memory>
#include "Log.h"
#include "Config.h"

class GameObject {
	std::vector<std::shared_ptr<GameObject>> children;
	std::weak_ptr<GameObject> parent;
	bool _has_parent = false;

	std::weak_ptr<GameObject> self;
	size_t hash = -1;

	static std::vector<std::shared_ptr<GameObject>> __objects;

	bool isStarted = false;
	bool isDestroyed = false;

	void __run_events();

	void __add_component(std::weak_ptr<GameObject> object);
public:

	Transform transform;

	template<typename T>
	static std::shared_ptr<T> Instantiate(std::shared_ptr<T> object, std::shared_ptr<GameObject> parent = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		object->self = object;
		// object->transform.setGameObject(object);
		object->hash = typeid(T).hash_code();
		if (parent != nullptr) {
			parent->__add_component(object);
		}
		else {
			__objects.push_back(object);
		}

		return object;
	}

	template<typename T>
	static std::shared_ptr<T> Instantiate(T* object, std::shared_ptr<GameObject> parent = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		auto objPtr = std::shared_ptr<T>(object);
		return Instantiate<T>(objPtr, parent);
	}

	static void Destroy(std::shared_ptr<GameObject> object, bool removeFromObjects = true);

	static void __RunStart();

	static void __RunEvents();

	template<typename T>
	bool is_type() {
		return hash == typeid(T).hash_code();
	}

	std::weak_ptr<GameObject> get_self_ptr();

	void remove_parent();
	void set_parent(std::shared_ptr<GameObject> parent);

	bool has_parent() {
		return _has_parent;
	}

	std::weak_ptr<GameObject> get_parent() {
		return parent;
	}

	Transform& get_transform() {
		return transform;
	}

	std::vector<std::shared_ptr<GameObject>> get_children() {
		return children;
	}

	virtual void on_destroy() {}
	virtual void start() {}
	virtual void update() {}

	template<typename T>
	std::shared_ptr<T> add_component(std::shared_ptr<T> child) {
		return Instantiate<T>(child, self.lock());
	}

	template<typename T>
	std::shared_ptr<GameObject> add_component(T* child) {
		return Instantiate<T>(child, self.lock());
	}
	void remove_component(std::weak_ptr<GameObject> child);

	// Disable copy constructor and assignment operator
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	GameObject() : transform(*this) {}
	~GameObject();
};