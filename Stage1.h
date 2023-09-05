#pragma once

#include <Novice.h>
#include "Player.h"

/// <summary>
/// ステージ1
/// </summary>
class Stage1
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stage1();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stage1();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	Player* player_ = nullptr; // 自機
};

