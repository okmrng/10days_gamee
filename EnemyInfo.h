#pragma once

#include <stdint.h>
#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// 敵情報
/// </summary>
class EnemyInfo
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyInfo();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyInfo();

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

public:
	// 敵
	uint32_t woodTexture_;  // 木のテクスチャハンドル
	uint32_t metalTexture_; // 金属製の箱のテクスチャハンドル
	uint32_t iceTexture_;   // 氷のテクスチャハンドル
	uint32_t tvTexture_;    // tvのテクスチャハンドル
};

