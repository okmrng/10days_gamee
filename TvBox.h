#pragma once

#include <Vector2.h>
#include <Novice.h>
#include <stdint.h>

// 前方宣言
class Player;

/// <summary>
/// tv
/// </summary>
class TvBox
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

	// セッター
	void SetPlayer(Player* player) { player_ = player; }

private:
	// 箱
	Vector2 pos_;        // 座標
	Vector2 size_;       // 横幅と縦幅
	float velocity_;     // 速度
	float acceleration_; // 加速度
	bool hit_;           // 当たったかの判定
	bool stop_;          // 他の箱に当てた時にも動くのを防止
	int32_t count_;      // tvのカウント
	uint32_t texture_;   // テクスチャハンドル
	uint32_t texture0_;  // 0のテクスチャハンドル
	uint32_t texture1_;  // 1のテクスチャハンドル
	uint32_t texture2_;  // 2のテクスチャハンドル
	uint32_t texture3_;  // 3のテクスチャハンドル

	// 自機
	Player* player_ = nullptr;
};

