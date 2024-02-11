#pragma once
#include <limits>
#include <cmath>

namespace Maths
{
	const float pi = 3.1415926535;
	const float twoPi = pi * 2.0f;
	const float piOvertTwo = pi / 2.0f;
	const float infinity = std::numeric_limits<float>::infinity();
	const float negInfinity = -std::numeric_limits<float>::infinity();

	inline float toRadians(float degrees) {
		return degrees * pi / 180.0f;
	}

	inline float toDegrees(float radians) {
		return radians * 180.0f / pi;
	}

	inline bool nearZero(float val, float epsilon = 0.001f) {
		return (fabs(val) <= epsilon);
	}

	template <typename T>
	T Max(const T& a, const T& b) {
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b) {
		return (a < b ? a : b);
	}

	template <typename T>
	T clamp(const T& value, const T& lower, const T& upper) {
		return min(upper,max(lower,value));
	}

	inline float abs(float value) {
		return fabs(value);
	}

	inline float cos(float value) {
		return cosf(value);
	}

	inline float sin(float value) {
		return sinf(value);
	}

	inline float tan(float value) {
		return tanf(value);
	}

	inline float acos(float value) {
		return acosf(value);
	}

	inline float atan2(float x, float y) {
		return atan2f(x, y);
	}

	inline float cot(float angle) {
		return 1.0f / tan(angle);
	}

	inline float lerp(float a, float b, float f) {
		return a + f * (b - a);
	}

	inline float sqrt(float value) {
		return sqrtf(value);
	}

	inline float fmod(float numer, float denom) {
		return std::fmod(numer, denom);
	}

	inline int round(float num) {
		return static_cast<int>(std::round(num));
	}

};

