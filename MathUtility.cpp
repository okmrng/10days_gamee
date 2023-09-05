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