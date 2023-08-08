#include "Color.h"

Vector3<float> Color::to_vec3() {
	return Vector3<float>(r * a, g * a, b * a);
}

Color::Color(Vector3<float>& v) {
	this->r = v.x;
	this->g = v.y;
	this->b = v.z;
	this->a = 1.0f;
}

Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
	a = 1;
}
