#include "Transform.h"
#include "GameObject.h"
#include "Config.h"

Transform::Transform() {}

Transform::Transform(Vector3<float> position, Vector3<float> scale) {}

// TODO: Implement based on the parent transform
void Transform::setPosition(Vector3<float> position) {
	ELOG_WARNING("World position set not implemented");
	this->position = position;
}

// TODO: Implement based on the parent transform
void Transform::setScale(Vector3<float> scale) {
	ELOG_WARNING("World scale set not implemented");
	this->scale = scale;
}

void Transform::setLocalPosition(Vector3<float> position) {
	this->position = position;
}

void Transform::setLocalScale(Vector3<float> scale) {
	this->scale = scale;
}

// TODO: Implement based on the parent transform
Vector3<float> Transform::getPosition() {
	ELOG_WARNING("World position get not implemented");
	return this->position;
}

// TODO: Implement based on the parent transform
Vector3<float> Transform::getScale() {
	ELOG_WARNING("World scale get not implemented");
	return this->scale;
}

Vector3<float> Transform::getLocalPosition() {
	return this->position;
}

Vector3<float> Transform::getLocalScale() {
	return this->scale;
}

void Transform::setGameObject(std::weak_ptr<GameObject> gameObject) {
#if SC_WARNING_ON 
	if (this->gameObject.lock() != nullptr) {
		ELOG_WARNING("Trying to set a gameObject to a transform that already has one");
	}
#endif
	this->gameObject = gameObject;
}

std::weak_ptr<GameObject> Transform::getGameObject() {
#if SC_FATAL_ON
	if (this->gameObject.lock() != nullptr) {
		ELOG_FATAL("Trying to get a gameObject from a transform that doesn't have one");
		return std::weak_ptr<GameObject>();
	}
#endif

	return this->gameObject;
}
