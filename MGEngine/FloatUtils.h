#pragma once
#include <math.h>

class FloatUtils {
public:
	bool static inline IsEqualApproximate(float a, float b, float epsilon = 0.00001f) {
		return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
	}
};