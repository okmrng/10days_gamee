#pragma once

#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// 押す箱
/// </summary>
class Box
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, Vector2 size);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 当たり判定が働いたときの処理
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	Vector2 GetPos() { return pos_; }
	Vector2 GetSize() { return size_; }

private:
	Vector2 pos_;    // 座標
	Vector2 size_;   // 横幅と縦幅
	float velocity_; // 速度
};

