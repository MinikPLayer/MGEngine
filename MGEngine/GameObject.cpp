#include "GameObject.h"

void GameObject::AddComponent(std::shared_ptr<GameObject> child) {
	children.push_back(child);
	if (!child->parent.expired()) {
		child->parent.lock().get()->RemoveComponent(child);
	}

	if (child->self.lock() == nullptr) {
		child->self = child;
	}

	child->parent = self;
}

void GameObject::RemoveComponent(std::shared_ptr<GameObject> child) {
	child->parent = std::weak_ptr<GameObject>();
	for (auto it = children.begin(); it != children.end(); ++it) {
		if (*it == child) {
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