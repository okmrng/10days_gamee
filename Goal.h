#pragma once

#include <Vector2.h>
#include <Novice.h>

class Goal
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="posY">ゴールのY座標</param>
	void Initialize(float posY);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ゴール
	Vector2 pos_;  // 座標
	Vector2 size_; //幅
};

