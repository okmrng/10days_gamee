﻿#pragma once

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
	void Initialize(int32_t canShoot);

	/// <summary>
	///  更新
	/// </summary>
	void Upadate(char* keys, char* preKeys);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(char* keys, char* preKeys);

	/// <summary>
	/// 弾の当たった時の処理
	/// </summary>
	void BulletOnCollision();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	Vector2 GetBulletCollisionPos();
	Vector2 GetBulletSize();
	int32_t GetBulletPower();

	// セッター
	void SetIsBullet(bool isBullet) { isBullet_ = isBullet; }

private:
	// 自機情報
	float radius_;   // 半径
	Vector2 pos_;    // 座標
	float velocity_; // 速度
	uint32_t color_; // 色

	// 弾
	PlayerBullet* bullet_ = nullptr;  // 弾のリスト
	int32_t charge_;                  // 弾のチャージ
	int32_t power_;                   // 弾のパワー
	int32_t canShoot_;                // 弾を撃つことができる回数
	bool isBullet_;                   // 弾フラグ
};

