#pragma once
struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(float xP, float yP) : x(xP), y(yP) {}

	float x;
	float y;
	static const Vector2 zero;
	static const Vector2 unitX;
	static const Vector2 unitY;
	static const Vector2 one;
	static const Vector2 null;

	void set(float xP, float yP);
	float lengthSq() const;
	float length() const;
	void normalize();

	static Vector2 normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.normalize();
		return temp;
	}

	static float dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static Vector2 lerp(const Vector2& a, const Vector2& b, float f)
	{
		return Vector2(a + f * (b - a));
	}

	friend bool operator==(const Vector2& left, const Vector2& right)
	{
		return (left.x == right.x && left.y == right.y);
	}

	friend bool operator!=(const Vector2& left, const Vector2& right)
	{
		return (left.x != right.x || left.y != right.y);
	}

	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	friend Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	friend Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	Vector2& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	friend Vector2 operator/(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x / scalar, vec.y / scalar);
	}

	friend Vector2 operator*(const Vector2& vec, const Vector2& vec2)
	{
		return Vector2(vec.x * vec2.x, vec.y * vec2.y);
	}
};