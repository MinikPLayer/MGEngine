#pragma once
#include "Vector3.h"
#include <memory>
#include <glm/glm.hpp>

class GameObject;
class Transform {
	glm::mat4 worldSpaceModelMatrix = glm::mat4(1.0f);
	GameObject& gameObject;

	Vector3<float> localPosition = Vector3<float>(0.0f, 0.0f, 0.0f);
	// TODO: rotation
	Vector3<float> localScale = Vector3<float>(1.0f, 1.0f, 1.0f);

	Vector3<float> globalPosition;
	// TODO: rotation
	Vector3<float> globalScale;

	glm::mat4 calculateLocalModelMatrix();

	void updateMatrix();
	
public:
	Transform(GameObject& gameObject);
	Transform(GameObject& gameObject, Vector3<float> position, Vector3<float> scale);

	glm::mat4 getWorldSpaceMatrix();

	void setPosition(Vector3<float> position);
	void setScale(Vector3<float> scale);

	void setLocalPosition(Vector3<float> position);
	void setLocalScale(Vector3<float> scale);

	Vector3<float> getForwardVector();
	Vector3<float> getUpVector();

	Vector3<float> getPosition();
	Vector3<float> getScale();

	Vector3<float> getLocalPosition();
	Vector3<float> getLocalScale();

	GameObject& getGameObject();
};

