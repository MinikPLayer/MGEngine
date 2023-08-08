#pragma once
#include <math.h>

class FloatUtils {
public:
	template <typename T>
	static int Sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	bool static inline IsEqualApproximate(float a, float b, float epsilon = 0.00001f) {
		return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}
};