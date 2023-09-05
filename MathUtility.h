#pragma once

#include <Vector2.h>

// 演算子オーバーロード
Vector2& operator-=(Vector2& v, float s);
const Vector2 operator-(const Vector2& v, float s);
