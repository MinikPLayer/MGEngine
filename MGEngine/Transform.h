#pragma once
#include "Vector3.h"
#include <memory>
#include <glm/glm.hpp>

class GameObject;
class Transform {
	Vector3<float> position;
	// TODO: rotation
	Vector3<float> scale;

	std::weak_ptr<GameObject> gameObject;
public:
	Transform();
	Transform(Vector3<float> position, Vector3<float> scale);

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

	void setGameObject(std::weak_ptr<GameObject> gameObject);
	std::weak_ptr<GameObject> getGameObject();
};

