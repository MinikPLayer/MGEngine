#include "Transform.h"
#include "GameObject.h"
#include "Config.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "MatrixUtils.h"

glm::mat4 Transform::calculate_local_model_matrix() {
	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, this->localPosition.to_glm());
	trans = trans * this->localRotation.rotation_matrix();
	trans = glm::scale(trans, this->localScale.to_glm());

	return trans;
}

void Transform::update_matrix() {
	auto parentMatrix = (gameObject.has_parent()) ? gameObject.get_parent().lock()->get_transform().get_world_space_matrix() : glm::mat4(1.0f);
	auto localMatrix = calculate_local_model_matrix();
	worldSpaceModelMatrix = parentMatrix * localMatrix;

	// TODO: Find a faster way to do this? 
	// Decompose is probably not the fastest way to do this
	// But should work for now
	auto dec = MatrixUtils::DecomposeMatrix(worldSpaceModelMatrix);

	this->globalPosition = Vector3<float>(dec.translation);
	this->globalScale = Vector3<float>(dec.scale);
	this->globalRotation = Quaternion(dec.rotation);

	for (auto child : gameObject.get_children()) {
		child->get_transform().update_matrix();
	}
}

Transform::Transform(GameObject& gameObject) : gameObject(gameObject) {}

Transform::Transform(GameObject& gameObject, Vector3<float> position, Vector3<float> scale) : gameObject(gameObject) {
	set_position(position);
	set_scale(scale);
}

glm::mat4 Transform::get_world_space_matrix() {
	return worldSpaceModelMatrix;
}

void Transform::set_position(Vector3<float> position) {
	if (gameObject.has_parent()) {
		auto parentMatrix = gameObject.get_parent().lock()->get_transform().get_world_space_matrix();
		auto parentInverse = glm::inverse(parentMatrix);
		auto localPosition = glm::vec4(position.to_glm(), 1.0f);
		auto relativePosition = parentInverse * localPosition;
		this->localPosition = Vector3<float>(relativePosition);
	}
	else {
		this->localPosition = position;
	}

	update_matrix();
}

void Transform::set_scale(Vector3<float> scale) {
	if (gameObject.has_parent()) {
		auto parentMatrix = gameObject.get_parent().lock()->get_transform().get_world_space_matrix();
		auto parentInverse = glm::inverse(parentMatrix);
		auto localScale = glm::vec4(scale.to_glm(), 1.0f);
		auto relativeScale = parentInverse * localScale;
		this->localScale = Vector3<float>(relativeScale);
	}
	else {
		this->localPosition = scale;
	}

	update_matrix();
}

void Transform::set_local_position(Vector3<float> position) {
	this->localPosition = position;

	update_matrix();
}

void Transform::set_local_scale(Vector3<float> scale) {
	this->localScale = scale;

	update_matrix();
}
void Transform::set_local_rotation(Quaternion quat) {
	this->localRotation = quat;

	update_matrix();
}

Vector3<float> Transform::get_forward_vector() {
	// TODO: Implement caching (maybe)
	return globalRotation.forward();
}

Vector3<float> Transform::get_up_vector() {
	return globalRotation.up();
}

Vector3<float> Transform::get_position() {
	return this->globalPosition;
}

Vector3<float> Transform::get_scale() {
	return this->globalScale;
}

Quaternion Transform::get_rotation() {
	return this->globalRotation;
}

Vector3<float> Transform::get_local_position() {
	return this->localPosition;
}

Vector3<float> Transform::get_local_scale() {
	return this->localScale;
}

Quaternion Transform::get_local_rotation() {
	return this->localRotation;
}

GameObject& Transform::get_gameobject() {
	return this->gameObject;
}
