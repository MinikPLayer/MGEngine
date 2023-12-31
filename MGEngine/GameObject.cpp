#include "GameObject.h"

void GameObject::__run_events() {
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

void GameObject::Destroy(std::shared_ptr<GameObject> object, bool removeFromObjects) {
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

void GameObject::__RunStart() {
	for (auto obj : __objects) {
		if (!obj->isStarted) {
			obj->start();
			obj->isStarted = true;
		}

	}
}

void GameObject::__RunEvents() {
	for (auto obj : __objects) {
		obj->__run_events();
	}
}

std::weak_ptr<GameObject> GameObject::get_self_ptr() {
#if SC_FATAL_ON
	if (self.lock() == nullptr) {
		ELOG_FATAL("Self pointer invalid. This could happen if getSelfPtr is called from the constructor. If that's the case, try calling it from the Start() method");
	}
#endif

	return self;
}

void GameObject::remove_parent() {
	if (has_parent()) {
		parent.lock()->remove_component(self);
	}

	_has_parent = false;
	parent.reset();
}
void GameObject::set_parent(std::shared_ptr<GameObject> _parent) {
	_parent->__add_component(this->self);
}
void GameObject::__add_component(std::weak_ptr<GameObject> child) {
	auto c = child.lock();
	children.push_back(c);

	c->remove_parent();

	if (c->self.lock() == nullptr) {
		c->self = child;
	}

	c->parent = self;
	c->_has_parent = true;

	c->transform.update_matrix();
}

void GameObject::__print_hierarchy__(int level) {
	std::stringstream ss;
	for (int i = 0; i < level; i++) {
		ss << "\t";
	}
	ss << typeid(*this).name();
	ELOG_INFO(ss.str());

	for (auto child : children) {
		child->__print_hierarchy__(level + 1);
	}
}

void GameObject::PrintObjectsHierarchy() {
	ELOG_INFO("\n\nObjects hierarchy:");
	for (auto obj : __objects) {
		obj->__print_hierarchy__(0);
	}
	ELOG_INFO("\n\n");
}

void GameObject::remove_component(std::weak_ptr<GameObject> child) {
	child.lock().get()->parent = std::weak_ptr<GameObject>();
	for (auto it = children.begin(); it != children.end(); ++it) {
		if (*it == child.lock()) {
			children.erase(it);
			break;
		}
	}
}

GameObject::~GameObject() {
	for (auto it = children.begin(); it != children.end(); ++it) {
		(*it)->parent = std::weak_ptr<GameObject>();
	}

	if (!isDestroyed) {
		on_destroy();
		isDestroyed = true;
	}

}

std::vector<std::shared_ptr<GameObject>> GameObject::__objects;