#pragma once

#include <Novice.h>
#include <Vector2.h>
#include <stdint.h>

/// <summary>
/// ポーズ
/// </summary>
class Pause
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 文字
	Vector2 PPos_;      // Pの座標
	Vector2 APos_;      // Aの座標
	Vector2 UPos_;      // Uの座標
	Vector2 SPos_;      // Sの座標
	Vector2 EPos_;      // Eの座標
	uint32_t PTexture_; // Pのテクスチャハンドル
	uint32_t ATexture_; // Aのテクスチャハンドル
	uint32_t UTexture_; // Uのテクスチャハンドル
	uint32_t STexture_; // Sのテクスチャハンドル
	uint32_t ETexture_; // Eのテクスチャハンドル
};

