#pragma once
#include "Transform.hpp"
#include <vector>
#include <memory>
#include "Log.hpp"
#include "Config.hpp"
#include "Event.hpp"
#include <functional>

//template<char ...TypeName>
class GameObject {
	std::vector<std::shared_ptr<GameObject>> children;
	std::weak_ptr<GameObject> parent;
	bool _has_parent = false;

	// TODO: This should be initialized before add component
	std::weak_ptr<GameObject> self;
	size_t hash = -1;

	static std::vector<std::shared_ptr<GameObject>> __objects;

	bool isStarted = false;
	bool isLateStarted = false;
	bool isDestroyed = false;

	void __run_event__(std::function<void(GameObject*)> func);

	void __add_component(std::weak_ptr<GameObject> object);

	void __print_hierarchy__(int level);
public:

	Transform transform;
	
	static void PrintObjectsHierarchy();

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

	static void __RunStart__();

	static void __RunUpdate__();

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

	const char* get_type_name() {
		return typeid(*this).name();
	}

	virtual void on_destroy() {}
	virtual void start() {}
	virtual void update() {}

	Event<GameObject*> lateStartEvent;
	Event<GameObject*> lateUpdateEvent;

	template<typename T>
	std::shared_ptr<T> add_component(std::shared_ptr<T> child) {
#if SC_WARNING_ON
		if (self.lock() == nullptr) {
			ELOG_WARNING("Trying to add component to uninitialized object");
		}
#endif	
		return Instantiate<T>(child, self.lock());
	}

	template<typename T>
	std::shared_ptr<T> add_component(T* child) {
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