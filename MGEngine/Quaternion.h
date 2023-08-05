#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Vector2.h"
#include "Vector3.h"

class Quaternion : public glm::quat {
public:
	static Quaternion from_euler(Vector3<float> v);

	[[nodiscard]]
	Vector3<float> forward();

	[[nodiscard]]
	Vector3<float> up();

	[[nodiscard]]
	Vector3<float> right();

	[[nodiscard]]
	Vector3<float> to_euler() const;

	[[nodiscard]]
	Quaternion rotated_around(Vector3<float> axis, float angle);

	[[nodiscard]]
	Quaternion normalized() const;

	void normalize(float tolerance = 0.0000001f);
	glm::mat4 rotation_matrix();

	static Quaternion identity();

	Quaternion() : glm::quat(1, 0, 0, 0) {}
	Quaternion(glm::quat q) : glm::quat(q) {}
	Quaternion(float v1, float v2, float v3, float v4) : glm::quat(v1, v2, v3, v4) {}
};
