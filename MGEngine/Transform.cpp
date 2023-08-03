#include "Transform.h"
#include "GameObject.h"
#include "Config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "MatrixUtils.h"

glm::mat4 Transform::calculateLocalModelMatrix() {
	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, this->localPosition.toGlm());
	// TODO: Add rotation here
	trans = glm::scale(trans, this->localScale.toGlm());

	return trans;
}

void Transform::updateMatrix() {
	auto parent = gameObject.getParent();
	auto parentMatrix = (parent.lock() == nullptr) ? glm::mat4(1.0f) : parent.lock()->getTransform().getWorldSpaceMatrix();
	auto localMatrix = calculateLocalModelMatrix();
	worldSpaceModelMatrix = parentMatrix * localMatrix;

	// TODO: Find a faster way to do this? 
	// Decompose is probably not the fastest way to do this
	// But should work for now
	auto dec = MatrixUtils::decomposeMatrix(worldSpaceModelMatrix);

	this->globalPosition = Vector3<float>(dec.translation);
	this->globalScale = Vector3<float>(dec.scale);
	// TODO: Add rotation here

	for (auto child : gameObject.getChildren()) {
		child->getTransform().updateMatrix();
	}
}

Transform::Transform(GameObject& gameObject) : gameObject(gameObject) {}

Transform::Transform(GameObject& gameObject, Vector3<float> position, Vector3<float> scale) : gameObject(gameObject) {
	setPosition(position);
	setScale(scale);
}

glm::mat4 Transform::getWorldSpaceMatrix() {
	return worldSpaceModelMatrix;
}

void Transform::setPosition(Vector3<float> position) {
	auto parent = gameObject.getParent();
	if (parent.lock() != nullptr) {
		auto parentMatrix = parent.lock()->getTransform().getWorldSpaceMatrix();
		auto parentInverse = glm::inverse(parentMatrix);
		auto localPosition = glm::vec4(position.toGlm(), 1.0f);
		auto relativePosition = parentInverse * localPosition;
		this->localPosition = Vector3<float>(relativePosition);
	}
	else {
		this->localPosition = position;
	}

	updateMatrix();
}

void Transform::setScale(Vector3<float> scale) {
	this->localScale = scale;

	updateMatrix(); 
}

void Transform::setLocalPosition(Vector3<float> position) {
	this->localPosition = position;

	updateMatrix();
}

void Transform::setLocalScale(Vector3<float> scale) {
	this->localScale = scale;

	updateMatrix();
}

Vector3<float> Transform::getForwardVector() {
	// TODO: Implement after implementing rotation
	return Vector3<float>(0, 0, 1);
}

Vector3<float> Transform::getUpVector() {
	// TODO: Implement after implementing rotation
	return Vector3<float>(0, 1, 0);
}

Vector3<float> Transform::getPosition() {
	return this->globalPosition;
}

Vector3<float> Transform::getScale() {
	return this->globalScale;
}

Vector3<float> Transform::getLocalPosition() {
	return this->localPosition;
}

Vector3<float> Transform::getLocalScale() {
	return this->localScale;
}

GameObject& Transform::getGameObject() {
	return this->gameObject;
}
