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

std::string Transform::to_string() {
	std::stringstream ss;
	ss << "Transform[Position: ";
	ss << this->globalPosition.to_string();
	ss << ", Rotation: ";
	ss << this->globalRotation.to_euler().to_string();
	ss << ", Scale: ";
	ss << this->globalScale.to_string();
	ss << "]";
	return ss.str();
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

// TODO: Fix incorrect behaviour
//void Transform::set_scale(Vector3<float> scale) {
//	if (gameObject.has_parent()) {
//		auto parentMatrix = gameObject.get_parent().lock()->get_transform().get_world_space_matrix();
//		auto parentInverse = glm::inverse(parentMatrix);
//		auto localScale = glm::scale(glm::mat4(1.0f), scale.to_glm());
//		auto relativeScale = parentInverse * localScale;
//		auto decomp = MatrixUtils::DecomposeMatrix(relativeScale);
//		this->localScale = Vector3<float>(decomp.scale);
//	}
//	else {
//		this->localPosition = scale;
//	}
//
//	update_matrix();
//}

void Transform::set_rotation(Quaternion quat) {
	if (gameObject.has_parent()) {
		auto parentMatrix = gameObject.get_parent().lock()->get_transform().get_world_space_matrix();
		auto parentInverse = glm::inverse(parentMatrix);
		auto localRotation = quat.rotation_matrix();
		auto relativeRotation = parentInverse * localRotation;
		auto decomp = MatrixUtils::GetRotation(relativeRotation);
		this->localRotation = Quaternion(decomp);
	}
	else {
		this->localRotation = quat;
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
