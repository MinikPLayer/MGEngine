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
	trans = trans * this->localRotation.rotation_matrix();
	trans = glm::scale(trans, this->localScale.toGlm());

	return trans;
}

void Transform::updateMatrix() {
	auto parentMatrix = (gameObject.has_parent()) ? gameObject.getParent().lock()->getTransform().getWorldSpaceMatrix() : glm::mat4(1.0f);
	auto localMatrix = calculateLocalModelMatrix();
	worldSpaceModelMatrix = parentMatrix * localMatrix;

	// TODO: Find a faster way to do this? 
	// Decompose is probably not the fastest way to do this
	// But should work for now
	auto dec = MatrixUtils::decomposeMatrix(worldSpaceModelMatrix);

	this->globalPosition = Vector3<float>(dec.translation);
	this->globalScale = Vector3<float>(dec.scale);
	this->globalRotation = Quaternion(dec.rotation);

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
	if (gameObject.has_parent()) {
		auto parentMatrix = gameObject.getParent().lock()->getTransform().getWorldSpaceMatrix();
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
void Transform::setLocalRotation(Quaternion quat) {
	this->localRotation = quat;

	updateMatrix();
}

Vector3<float> Transform::getForwardVector() {
	// TODO: Implement caching (maybe)
	return globalRotation.forward();
}

Vector3<float> Transform::getUpVector() {
	return globalRotation.up();
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
