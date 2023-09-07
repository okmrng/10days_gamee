#include "MathUtility.h"

Vector2& operator-=(Vector2& v, float s) {
	v.x -= s;
	v.y -= s;

	return v;
}

const Vector2 operator-(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp -= s;
}

Vector2& operator/=(Vector2& v, float s) {
	v.x /= s;
	v.y /= s;

	return v;
}

const Vector2 operator/(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp /= s;
}

Vector2& operator+=(Vector2& v1, const Vector2& v2) {
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 result = v1;
	return result += v2;
}