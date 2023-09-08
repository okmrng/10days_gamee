#pragma once

#include <stdint.h>
#include <Novice.h>

/// <summary>
/// ステージセレクト
/// </summary>
class StageSelect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelect();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initiallize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(char* keys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター
	bool GetToNext() { return toNext_; }

private:
	bool toNext_; // 次のシーンへ

	int32_t pushCount_; // キーが押せるようになるまでのカウント
};

