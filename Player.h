#pragma once

#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// 自機クラス
/// </summary>
class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///  更新
	/// </summary>
	void Upadate(char* keys, char* preKeys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 自機情報
	float radius_;     // 半径
	Vector2 pos_;      // 座標
	float velocity_;   // 速度
};

