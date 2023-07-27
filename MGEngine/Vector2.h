#pragma once

#include <math.h>
#include "FloatUtils.h"
#include <string>
#include <sstream>

template<typename T>
class Vector2 {
public:
	T x, y;

	Vector2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	}

	bool IsEqualExact(Vector2<T> const& v) const {
		return x == v.x && y == v.y;
	}

	bool IsEqualApproximate(Vector2<T> const& v, float epsilon = 0.00001f) const {
		return FloatUtils::IsEqualApproximate(x, v.x, epsilon) &&
			FloatUtils::IsEqualApproximate(y, v.y, epsilon);
	}

	Vector2<T> operator+(Vector2<T> const& v) {
		return Vector2<T>(v.x + x, v.y + y);
	}
	Vector2<T> operator-(Vector2<T> const& v) {
		return Vector2<T>(x - v.x, y - v.y);
	}
	Vector2<T> operator*(float const& f) {
		return Vector2<T>(x * f, y * f);
	}
	Vector2<T> operator/(float const& f) {
		return Vector2<T>(x / f, y / f);
	}

	float dot(Vector2<T> const& v) {
		return v.x * x + v.y * y;
	}

	T sqrMagnitude() {
		return x * x + y * y;
	}

	double magnitude() {
		return sqrt(sqrMagnitude());
	}

	Vector2<T> normalized() {
		return *this / magnitude();
	}

	std::string toString() const {
		std::stringstream ss;
		ss << "(" << x << ", " << y << ")";
		return ss.str();
	}
};
