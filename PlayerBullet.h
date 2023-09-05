#pragma once

#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// 自機に弾
/// </summary>
class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, float velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	bool GetIsDead() { return isDead_; }
	
private:
	float radius_;   // 半径
	Vector2 pos_;    // 座標
	float velocity_; // 速度
	bool isDead_;    // デスフラグ
};

