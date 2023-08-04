#include "GameObject.h"

void GameObject::remove_parent() {
	if (has_parent()) {
		parent.lock()->RemoveComponent(self);
	}

	_has_parent = false;
	parent.reset();
}
void GameObject::set_parent(std::shared_ptr<GameObject> _parent) {
	_parent->AddComponent(this->self);
}
void GameObject::AddComponent(std::weak_ptr<GameObject> child) {
	auto c = child.lock();
	children.push_back(c);

	c->remove_parent();

	if (c->self.lock() == nullptr) {
		c->self = child;
	}

	c->parent = self;
	c->_has_parent = true;
}

void GameObject::RemoveComponent(std::weak_ptr<GameObject> child) {
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
		OnDestroy();
		isDestroyed = true;
	}

}

std::vector<std::shared_ptr<GameObject>> GameObject::__objects;