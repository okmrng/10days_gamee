﻿#pragma once

#include <Novice.h>
#include <stdint.h>
#include <MathUtility.h>

/// <summary>
/// ゲームオーバー
/// </summary>
class GameOver
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="keys">キー1</param>
	/// <param name="preKeys">キー2</param>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 背景
	uint32_t backgroundColor_; // 色
	uint32_t backgroundAlpha_; // 透明度

	// FAILED
	uint32_t failedTexture_; // テクスチャハンドル
	uint32_t color_;         // 色
	uint32_t alpha_;         // 透明度
};

