#pragma once

#include <stdint.h>
#include <Novice.h>
#include <Vector2.h>

/// <summary>
/// ヒットエフェクト
/// </summary>
class HitEffect
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t texture, uint32_t anim, uint32_t animMax, uint32_t flame, uint32_t flameMax,
		Vector2 pos, Vector2 size);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	uint32_t texture_;	  // テクスチャハンドル
	uint32_t anim_;		  // アニメーション
	uint32_t animMax_;    // アニメーションの最大値
	uint32_t flame_;	  // フレーム
	uint32_t flameMax_;   // フレームの最大値
	Vector2 pos_;         // 位置
	Vector2 size_;        // 幅
};

