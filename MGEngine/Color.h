#pragma once
#include "Vector3.h"

class Color {
public:
	float r, g, b, a;

	Vector3<float> toVector3();

	Color(Vector3<float>& v);
	Color(float r, float g, float b, float a = 1.0f);
	Color();
};