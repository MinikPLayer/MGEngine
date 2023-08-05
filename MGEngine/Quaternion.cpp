#include "Quaternion.h"

Quaternion Quaternion::from_euler(Vector3<float> v) {
	return { glm::quat(v.to_glm()) };
}

[[nodiscard]]
Vector3<float> Quaternion::forward() {
	return glm::rotate(glm::inverse(*this), glm::vec3(0.0, 0.0, 1.0));
}

[[nodiscard]]
Vector3<float> Quaternion::up() {
	return glm::rotate(glm::inverse(*this), glm::vec3(0.0, 1.0, 0.0));
}

[[nodiscard]]
Vector3<float> Quaternion::right() {
	return glm::rotate(glm::inverse(*this), glm::vec3(1.0, 0.0, 0.0));
}

[[nodiscard]]
Vector3<float> Quaternion::to_euler() const {
	return glm::eulerAngles(*this);
}

[[nodiscard]]
Quaternion Quaternion::rotated_around(Vector3<float> axis, float angle) {
	auto quat = Quaternion::from_euler(axis * angle);

	return *this * quat;
}

[[nodiscard]]
Quaternion Quaternion::normalized() const {
	auto ret = Quaternion(*this);
	ret.normalize();
	return ret;
}

void Quaternion::normalize(float tolerance) {
	float mag2 = x * x + y * y + z * z + w * w;
	if (mag2 - 1.0f > tolerance) {
		float mag = sqrt(mag2);
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
}

glm::mat4 Quaternion::rotation_matrix() {
	return glm::toMat4(*this);
}

Quaternion Quaternion::identity() {
	return Quaternion();
}
