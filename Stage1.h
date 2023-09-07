#pragma once

#include <Novice.h>
#include "Player.h"
#include "Box.h"
#include "MetalBox.h"
#include "IceBox.h"
#include "TvBox.h"
#include "Clear.h"
#include "GameOver.h"
#include <list>
#include <sstream>
#include <cassert>

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
	/// 箱発生データの読み込み
	/// </summary>
	void LoadData(const std::string& filename, std::stringstream& targetStream);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(char* keys, char* preKeys);

	/// <summary>
	/// 当たり判定
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// 木箱生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">大きさ</param>
	void AddBox(Vector2 pos, Vector2 size);

	/// <summary>
	/// 金属製の箱生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">大きさ</param>
	void AddMetalBox(Vector2 pos, Vector2 size);

	/// <summary>
	/// 氷生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">大きさ</param>
	void AddIceBox(Vector2 pos, Vector2 size);

	/// <summary>
	/// tv生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="size">大きさ</param>
	void AddTvBox(Vector2 pos, Vector2 size);

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateBoxComands();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	Player* player_ = nullptr; // 自機

	// 箱
	std::list<Box*> box_;           // 木箱
	std::list<MetalBox*> metalBox_; // 金属製の箱
	std::list<IceBox*> iceBox_;     // 氷
	std::list<TvBox*> tvBox_;       // tv

	Clear* clear_; // クリア

	GameOver* gameOver_; // ゲームオーバー

	std::stringstream boxPopComands_; // 発生コマンド

	int32_t clearCount_; // クリア判定

	bool isGameOver_; // ゲームオーバーフラグ

	bool canPlay_; // プレイフラグ
};

