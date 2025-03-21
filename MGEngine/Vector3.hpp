#pragma once
#include <math.h>
#include "FloatUtils.hpp"
#include <string>
#include <glm/glm.hpp>
#include <sstream>

// TODO: Merge Vector3 and Vector2 into one class with template
template<typename T>
class Vector3 {
public:
	T x, y, z;

	Vector3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(glm::vec3 v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}

	bool is_equal_exact(Vector3<T> const& v) const {
		return x == v.x && y == v.y && z == v.z;
	}

	bool is_equal_approximate(Vector3<T> const& v, float epsilon = 0.00001f) const {
		return FloatUtils::IsEqualApproximate((float) x, (float)v.x, epsilon) &&
			FloatUtils::IsEqualApproximate((float)y, (float)v.y, epsilon) &&
			FloatUtils::IsEqualApproximate((float)z, (float)v.z, epsilon);
	}

	glm::vec3 to_glm() {
		return glm::vec3(x, y, z);
	}

	Vector3<T> operator+(Vector3<T> const& v) {
		return Vector3<T>(v.x + x, v.y + y, v.z + z);
	}
	Vector3<T> operator-(Vector3<T> const& v) {
		return Vector3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vector3<T> operator*(float const& f) {
		return Vector3<T>(x * f, y * f, z * f);
	}
	Vector3<T> operator/(float const& f) {
		return Vector3<T>(x / f, y / f, z / f);
	}

	float dot(Vector3<T> const& v) {
		return (float)(v.x * x + v.y * y + v.z * z);
	}

	Vector3<T> cross(Vector3<T> const& v) {
		return Vector3<T>(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	T sqr_magnitude() {
		return x * x + y * y + z * z;
	}

	double magnitude() {
		return sqrt(sqr_magnitude());
	}

	Vector3<T> normalized() {
		return *this / magnitude();
	}

	std::string to_string() const {
		std::stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}
};
