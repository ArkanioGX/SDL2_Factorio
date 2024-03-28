#pragma once
#include <limits>
#include <cmath>

namespace Maths
{
	const float pi = 3.1415926535f;
	const float twoPi = pi * 2.0f;
	const float piOver2 = pi / 2.0f;
	const float infinity = std::numeric_limits<float>::infinity();
	const float negInfinity = -std::numeric_limits<float>::infinity();

	inline float toRadians(float degrees)
	{
		return degrees * pi / 180.0f;
	}

	inline float toDegrees(float radians)
	{
		return radians * 180.0f / pi;
	}

	inline bool nearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T clamp(const T& value, const T& lower, const T& upper)
	{
		return min(upper, max(lower, value));
	}

	inline float abs(float value)
	{
		return fabs(value);
	}

	inline float cos(float angle)
	{
		return cosf(angle);
	}

	inline float sin(float angle)
	{
		return sinf(angle);
	}

	inline float tan(float angle)
	{
		return tanf(angle);
	}

	inline float acos(float value)
	{
		return acosf(value);
	}

	inline float atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float cot(float angle)
	{
		return 1.0f / tan(angle);
	}

	inline float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float fmod(float numer, float denom)
	{
		return std::fmod(numer, denom);
	}

	inline int round(float num)
	{
		return static_cast<int>(std::round(num));
	}

	inline float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime,float maxSpeed = infinity ,float deltaTime = 1.0f/60.0f)
	{
		// Based on Game Programming Gems 4 Chapter 1.10
		smoothTime = Maths::max(0.0001F, smoothTime);
		float omega = 2.0f / smoothTime;

		float x = omega * deltaTime;
		float exp = 1.0F / (1.0F + x + 0.48F * x * x + 0.235F * x * x * x);
		float change = current - target;
		float originalTo = target;

		// Clamp maximum speed
		float maxChange = maxSpeed * smoothTime;
		change = Maths::clamp(change, -maxChange, maxChange);
		target = current - change;

		float temp = (currentVelocity + omega * change) * deltaTime;
		currentVelocity = (currentVelocity - omega * temp) * exp;
		float output = target + (change + temp) * exp;

		// Prevent overshooting
		if (originalTo - current > 0.0F == output > originalTo)
		{
			output = originalTo;
			currentVelocity = (output - originalTo) / deltaTime;
		}

		return output;
	}
}