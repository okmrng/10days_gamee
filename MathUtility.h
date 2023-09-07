#pragma once

#include <Vector2.h>
#include <cmath>

// 演算子オーバーロード
Vector2& operator-=(Vector2& v, float s);
const Vector2 operator-(const Vector2& v, float s);

Vector2& operator/=(Vector2& v, float s);
const Vector2 operator/(const Vector2& v, float s);

Vector2& operator+=(Vector2& v1, const Vector2& v2);
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
