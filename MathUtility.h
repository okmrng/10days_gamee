#pragma once

#include <Vector2.h>
#include <cmath>

// 関数
/// <summary>
/// イーズアウト
/// </summary>
/// <param name="pos">座標セット</param>
/// <param name="startPoint">始点</param>
/// <param name="endPoint">終点</param>
/// <param name="endPoint">フレーム</param>
float EaseOutCirc(float pos, float startPoint, float endPoint, float t);

// 演算子オーバーロード
Vector2& operator-=(Vector2& v, float s);
const Vector2 operator-(const Vector2& v, float s);
