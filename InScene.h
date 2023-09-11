#pragma once

#include <Novice.h>
#include <MathUtility.h>
#include <stdint.h>

/// <summary>
/// シーン遷移(入)
/// </summary>
class InScene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 弾
	float fistPosX_;       // 位置
	float t_;              // フレーム
	uint32_t fistTexture_; // テクスチャ

	// 黒
	float blackPosX_; // 位置
};

