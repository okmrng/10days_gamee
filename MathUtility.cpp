#include "MathUtility.h"

float EaseOutCirc(float pos, float startPoint, float endPoint, float t)
{
	if (t < 1.0f) {
		t += 1.0f / 30.0f;
	}
	if (t >= 1.0f) {
		t = 1.0f;
	}

	float easedT_ = sqrt(1.0f - pow(t - 1.0f, 2.0f));

	pos = (1.0f - easedT_) * startPoint + easedT_ * endPoint;

	return pos;
}

Vector2& operator-=(Vector2& v, float s) {
	v.x -= s;
	v.y -= s;

	return v;
}

const Vector2 operator-(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp -= s;
}