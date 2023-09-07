#pragma once

#include <stdint.h>
#include <Novice.h>

/// <summary>
/// タイトル
/// </summary>
class Title
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="keys">キー</param>
	void Update(char* keys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	bool GetToNext() { return toNext_; }

private:
	// 画像
	uint32_t texture_; // テクスチャハンドル
	uint32_t color_;   // 色
	uint32_t alpha_;   // 透明度
	bool isFade_;      // フェードアウトフラグ

	bool toNext_; // 次のシーンへ遷移するためのフラグ
};

