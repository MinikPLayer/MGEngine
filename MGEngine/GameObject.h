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

	void __run_events() {
#if !NDEBUG
		if (isDestroyed) {
			ELOG_ERROR("Destroyed object is still running events");
		}
#endif

		if (!isStarted) {
			start();
			isStarted = true;
		}

		update();

		for (auto c : children) {
			c->__run_events();
		}
	}
public:

	Transform transform;

	template<typename T>
	static std::shared_ptr<T> Instantiate(std::shared_ptr<T> object, std::shared_ptr<GameObject> parent = nullptr) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

		object->self = object;
		// object->transform.setGameObject(object);
		object->hash = typeid(T).hash_code();
		if (parent != nullptr) {
			parent->AddComponent(object);
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

	static void Destroy(std::shared_ptr<GameObject> object, bool removeFromObjects = true) {
#if !NDEBUG
		if (object->isDestroyed) {
			ELOG_ERROR("Object destoyed twice");
		}
#endif

		if (!object->parent.expired()) {
			object->parent.lock()->remove_component(object);
		}

		object->on_destroy();
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
				obj->start();
				obj->isStarted = true;
			}

		}
	}

	static void __RunEvents() {
		for (auto obj : __objects) {
			obj->__run_events();
		}
	}

	template<typename T>
	bool is_type() {
		return hash == typeid(T).hash_code();
	}

	std::weak_ptr<GameObject> get_self_ptr() {
#if SC_FATAL_ON
		if (self.lock() == nullptr) {
			ELOG_FATAL("Self pointer invalid. This could happen if getSelfPtr is called from the constructor. If that's the case, try calling it from the Start() method");
		}
#endif

		return self;
	}

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

	void add_component(std::weak_ptr<GameObject> child);
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