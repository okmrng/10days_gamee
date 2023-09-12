#pragma once

#include <stdint.h>
#include <Novice.h>

/// <summary>
/// 制限時間
/// </summary>
class TimeLimit
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="timeLimit">制限時間</param>
	void Initialize(int32_t timeLimit);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	int32_t timeLimit_; // 制限時間
	int32_t time_;      // 値で画像の割り当て

	uint32_t textureHandleNumber_[10]; // テクスチャハンドル

	int32_t width_;     // 画像の横幅

	int32_t eachTime_[2];  // 画像の割り当て
};

