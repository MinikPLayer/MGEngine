#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Vector2.h"
#include "Vector3.h"

class Quaternion : public glm::quat {
public:
	static Quaternion from_euler(Vector3<float> v) {
		return { glm::quat(v.to_glm()) };
	}

	[[nodiscard]]
	Vector3<float> forward() {
		return glm::rotate(glm::inverse(*this), glm::vec3(0.0, 0.0, 1.0));
	}

	[[nodiscard]]
	Vector3<float> up() {
		return glm::rotate(glm::inverse(*this), glm::vec3(0.0, 1.0, 0.0));
	}

	[[nodiscard]]
	Vector3<float> right() {
		return glm::rotate(glm::inverse(*this), glm::vec3(1.0, 0.0, 0.0));
	}

	[[nodiscard]]
	Vector3<float> to_euler() const {
		return glm::eulerAngles(*this);
	}

	[[nodiscard]]
	Quaternion normalized() const {
		auto ret = Quaternion(*this);
		ret.normalize();
		return ret;
	}

	void normalize(float tolerance = 0.0000001f) {
		float mag2 = x * x + y * y + z * z + w * w;
		if (mag2 - 1.0f > tolerance) {
			float mag = sqrt(mag2);
			x /= mag;
			y /= mag;
			z /= mag;
			w /= mag;
		}
	}
	glm::mat4 rotation_matrix() {
		return glm::toMat4(*this);
	}

	static Quaternion identity() {
		return Quaternion(0, 0, 0, 0);
	}

	Quaternion() : glm::quat() {}
	Quaternion(glm::quat q) : glm::quat(q) {}
	Quaternion(float v1, float v2, float v3, float v4) : glm::quat(v1, v2, v3, v4) {}
};
