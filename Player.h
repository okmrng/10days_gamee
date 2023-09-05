#pragma once

#include <Vector2.h>
#include <Novice.h>
#include "PlayerBullet.h"
#include <list>

/// <summary>
/// 自機クラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///  更新
	/// </summary>
	void Upadate(char* keys, char* preKeys);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(char* keys, char* preKeys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 自機情報
	float radius_;     // 半径
	Vector2 pos_;      // 座標
	float velocity_;   // 速度

	// 弾
	std::list<PlayerBullet*> bullet_; // 弾のリスト
};

