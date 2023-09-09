﻿#include "Stage1.h"
#include <fstream>

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete player_;
	for (Box* box : box_) {
		delete box;
	}
	for (MetalBox* metalBox : metalBox_) {
		delete metalBox;
	}
	for (IceBox* iceBox : iceBox_) {
		delete iceBox;
	}
	for (TvBox* tvBox : tvBox_) {
		delete tvBox;
	}
	delete clear_;
	delete gameOver_;
	delete pause_;
}

void Stage1::Initialize()
{
	// 自機
	player_ = new Player();
	player_->Initialize();

	// クリア
	clear_ = new Clear();

	// ゲームオーバー
	gameOver_ = new GameOver();

	// ポーズ
	pause_ = new Pause();
	pause_->Initialize();

	// コマンド
	LoadData("resource/csv/boxData1.csv", boxPopComands_);
	 
	// クリア判定
	clearCount_ = 0;

	// クリア関連
	isClear_ = false;
	toClearCount_ = 30;

	// ゲームオーバー
	isGameOver_ = false;
	inGameOverCount_ = 60 * 3;

	// プレイ
	canPlay_ = false;
	playCount_ = 5;
	isStart_ = true;

	// ポーズ
	isPause_ = false;
	replay_ = false;

	// テクスチャハンドル
	metalHitEffect_ = Novice::LoadTexture("./resource/effect/metal-Effect.png");
	iceHitEffect_ = Novice::LoadTexture("./resource/effect/ice-Effect.png");
	woodHitEffect_ = Novice::LoadTexture("./resource/effect/wood-Effect.png");
	tvHitEffect_ = Novice::LoadTexture("./resource/effect/tv-Effect.png");

	// 制限時間
	time_ = 9999999;
	timeLimit_ = time_;
}

void Stage1::LoadData(const std::string& filename, std::stringstream& targetStream)
{
	std::ifstream file;
	// ファイルを開く
	file.open(filename);
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	// 文字列ストリームをクリア
	targetStream.str("");
	targetStream << file.rdbuf();

	// ファイルを閉じる
	file.close();

	// ファイルを再度開いてポインタを先頭に戻す
	file.open(filename);
	assert(file.is_open());

	// エラーフラグをクリア
	file.clear();
	// ファイルポインタを先頭に戻す
	file.seekg(0, std::ios::beg);
	// 再度ファイルを閉じる
	file.close();
}

void Stage1::Update(char* keys, char* preKeys)
{
	// スタート
	if(isStart_){
		--playCount_;
		player_->SetCanShoot(bulletCount_);
		timeLimit_ = time_;
		if (playCount_ <= 0) {
			canPlay_ = true;
			isStart_ = false;
		}
	}

	// 箱
	UpdateBoxComands();

	if(canPlay_){
		// 自機
		player_->Upadate(keys, preKeys);

		// 木箱
		for (Box* box : box_) {
			box->Update();
		}

		//	金属製の箱
		for (MetalBox* metalBox : metalBox_) {
			metalBox->Update();
		}

		// 氷
		for (IceBox* iceBox : iceBox_) {
			iceBox->Update();
		}

		// tv
		for (TvBox* tvBox : tvBox_) {
			tvBox->Update();
		}

		// 当たり判定
		CheckAllCollision();

		// クリア
		if (clearCount_ == boxCount_) {
			isClear_ = true;
			if(--toClearCount_<=0){
				canPlay_ = false;
			}
		}

		// ゲームオーバー
		if (player_->GetCanShoot() <= 0) {
			--inGameOverCount_;
		}
		if (inGameOverCount_ <= 0) {
			isGameOver_ = true;
			canPlay_ = false;
		}

		// プレイ中はポーズを初期化
		pause_->Initialize();

		// ポーズへ
		if (keys[DIK_P] && preKeys[DIK_P] == 0) {
			isPause_ = true;
			canPlay_ = false;
		}

		// ヒットエフェクト
		if(hitEffect_){
			hitEffect_->Update();
		}
		
		// 制限時間減らす
		--timeLimit_;
	}

	// ポーズ
	if (isPause_) {
		pause_->Update(keys, preKeys);

		// 再開
		if (pause_->GetToPlay()) {
			if(!replay_){
				playCount_ = 5;
				replay_ = true;
			}
			else if (replay_) {
				--playCount_;
				if (playCount_ <= 0) {
					replay_ = false;
					canPlay_ = true;
					isPause_ = false;
				}
			}
		}
	}
}

void Stage1::CheckAllCollision()
{
	// 判定用の変数
	Vector2 posA, posB;   // 座標
	Vector2 sizeA, sizeB; // 幅

	// 木箱
	// 自弾との当たり判定
	#pragma region
	// 自弾
	posB = player_->GetBulletCollisionPos(); // 座標
	sizeB = player_->GetBulletSize();		   // 幅
	for (Box* box : box_) {
		// 箱
		posA = box->GetPos();   // 座標
		sizeA = box->GetSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			// ヒットエフェクト
			AddHitEffect(woodHitEffect_, 0, 3, 0, 3, Vector2(posB.x, posB.y - 42), Vector2(52, 100));
			// 箱
			box->OnCollision();
			// 自弾
			player_->BulletOnCollision();
		}
	}
	#pragma endregion

	// ゴールとの当たり判定
	#pragma region
	for (Box* box : box_) {
		// 箱
		posA = box->GetPos();   // 座標
		sizeA = box->GetSize(); // 幅

		// ゴール
		posB = box->GetGoalCollisionPos();	//座標
		sizeB = box->GetGoalCollisionSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			if (box->GetVelocity() <= 15) {
				if (!box->GetAddStop()) {
					clearCount_++;
				}
				box->IsGoal();
			}
		}
	}
	#pragma endregion

	// 金属製の箱
	// 自弾との当たり判定
	#pragma region
	// 自弾
	posB = player_->GetBulletCollisionPos(); // 座標
	sizeB = player_->GetBulletSize();		   // 幅
	for (MetalBox* metalBox : metalBox_) {
		// 箱
		posA = metalBox->GetPos();   // 座標
		sizeA = metalBox->GetSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			// ヒットエフェクト
			AddHitEffect(metalHitEffect_, 0, 3, 0, 3, Vector2(posB.x, posB.y - 42), Vector2(52, 100));
			// 箱
			metalBox->OnCollision();
			// 自弾
			player_->BulletOnCollision();
		}
	}
	#pragma endregion

	// ゴールとの当たり判定
	#pragma region
	for (MetalBox* metalBox : metalBox_) {
		// 箱
		posA = metalBox->GetPos();   // 座標
		sizeA = metalBox->GetSize(); // 幅

		// ゴール
		posB = metalBox->GetGoalCollisionPos();	//座標
		sizeB = metalBox->GetGoalCollisionSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			if (metalBox->GetVelocity() <= 15) {
				if (!metalBox->GetAddStop()) {
					clearCount_++;
				}
				metalBox->IsGoal();
			}
		}
	}
	#pragma endregion

	// 氷
	// 自弾との当たり判定
	#pragma region
	// 自弾
	posB = player_->GetBulletCollisionPos(); // 座標
	sizeB = player_->GetBulletSize();		   // 幅
	for (IceBox* iceBox : iceBox_) {
		// 箱
		posA = iceBox->GetPos();   // 座標
		sizeA = iceBox->GetSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			// ヒットエフェクト
			AddHitEffect(iceHitEffect_, 0, 3, 0, 3, Vector2(posB.x, posB.y - 42), Vector2(50, 100));
			// 箱
			iceBox->OnCollision();
			// 自弾
			player_->BulletOnCollision();
		}
	}
	#pragma endregion

	// ゴールとの当たり判定
	#pragma region
	for (IceBox* iceBox : iceBox_) {
		// 箱
		posA = iceBox->GetPos();   // 座標
		sizeA = iceBox->GetSize(); // 幅

		// ゴール
		posB = iceBox->GetGoalCollisionPos();	//座標
		sizeB = iceBox->GetGoalCollisionSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			if (iceBox->GetVelocity() <= 15) {
				if (!iceBox->GetAddStop()) {
					clearCount_++;
				}
				iceBox->IsGoal();
			}
		}
	}
	#pragma endregion

	// tv
	// 自弾との当たり判定
	#pragma region
	// 自弾
	posB = player_->GetBulletCollisionPos(); // 座標
	sizeB = player_->GetBulletSize();		   // 幅
	for (TvBox* tvBox : tvBox_) {
		// 箱
		posA = tvBox->GetPos();   // 座標
		sizeA = tvBox->GetSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			// ヒットエフェクト
			AddHitEffect(tvHitEffect_, 0, 3, 0, 4, Vector2(posB.x, posB.y - 42), Vector2(60, 100));
			// 箱
			tvBox->OnCollision();
			// 自弾
			player_->BulletOnCollision();
		}
	}
	#pragma endregion

	// ゴールとの当たり判定
	#pragma region
	for (TvBox* tvBox : tvBox_) {
		// 箱
		posA = tvBox->GetPos();   // 座標
		sizeA = tvBox->GetSize(); // 幅

		// ゴール
		posB = tvBox->GetGoalCollisionPos();	//座標
		sizeB = tvBox->GetGoalCollisionSize(); // 幅

		if (posB.x < posA.x + sizeA.x && posA.x < posB.x + sizeB.x &&
			posB.y < posA.y + sizeA.y && posA.y < posB.y + sizeB.y) {
			if (tvBox->GetVelocity() <= 15) {
				if (!tvBox->GetAddStop()) {
					clearCount_++;
				}
				tvBox->IsGoal();
			}
		}
	}
	#pragma endregion
}

void Stage1::AddBox(Vector2 pos, Vector2 size)
{
	// 弾の生成
	Box* obj = new Box();
	// 初期化
	obj->Initialize(pos, size);
	// 自機をセット
	obj->SetPlayer(player_);

	box_.push_back(obj);
}

void Stage1::AddMetalBox(Vector2 pos, Vector2 size)
{
	// 弾の生成
	MetalBox* obj = new MetalBox();
	// 初期化
	obj->Initialize(pos, size);
	// 自機をセット
	obj->SetPlayer(player_);

	metalBox_.push_back(obj);
}

void Stage1::AddIceBox(Vector2 pos, Vector2 size)
{
	// 弾の生成
	IceBox* obj = new IceBox();
	// 初期化
	obj->Initialize(pos, size);
	// 自機をセット
	obj->SetPlayer(player_);

	iceBox_.push_back(obj);
}

void Stage1::AddTvBox(Vector2 pos, Vector2 size)
{
	// 弾の生成
	TvBox* obj = new TvBox();
	// 初期化
	obj->Initialize(pos, size);
	// 自機をセット
	obj->SetPlayer(player_);

	tvBox_.push_back(obj);
}

void Stage1::AddHitEffect(uint32_t texture, uint32_t anim, uint32_t animMax, 
	uint32_t flame, uint32_t flameMax, Vector2 pos, Vector2 size)
{
	// 生成
	hitEffect_ = new HitEffect();
	// 初期化
	hitEffect_->Initialize(texture,  anim,  animMax, flame, flameMax, pos, size);
}

void Stage1::UpdateBoxComands()
{
	// 1行分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(boxPopComands_, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {
			// 座標
			// x座標
			getline(line_stream, word, ',');
			float posX = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float posY = (float)std::atof(word.c_str());

			// サイズ
			// 横幅
			getline(line_stream, word, ',');
			float width = (float)std::atof(word.c_str());

			// 縦幅
			getline(line_stream, word, ',');
			float height = (float)std::atof(word.c_str());

			// 敵の種類
			getline(line_stream, word, ',');
			int32_t kinds = atoi(word.c_str());

			if(kinds == 1){
				AddBox(Vector2(posX, posY), Vector2(width, height));
			}
			if (kinds == 2) {
				AddMetalBox(Vector2(posX, posY), Vector2(width, height));
			}
			if (kinds == 3) {
				AddIceBox(Vector2(posX, posY), Vector2(width, height));
			}
			if (kinds == 4) {
				AddTvBox(Vector2(posX, posY), Vector2(width, height));
			}
		}
		// COUNTコマンド
		else if (word.find("COUNT") == 0) {
			getline(line_stream, word, ',');
			boxCount_ = atoi(word.c_str());
		}
		// BULLETコマンド
		else if (word.find("BULLET") == 0) {
			getline(line_stream, word, ',');
			bulletCount_ = atoi(word.c_str());
		}
		// TIMEコマンド
		else if (word.find("TIME") == 0) {
			getline(line_stream, word, ',');
			time_ = atoi(word.c_str());
		}
	}
}

void Stage1::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	// 自機
	player_->Draw(isGameOver_);

	// ゴール上の直線
	Novice::DrawBox(1047, 0, 5, 720, 0.0f, GREEN, kFillModeSolid);

	// 箱
	// 木箱
	for (Box* box : box_) {
		box->Draw();
	}

	// 金属製の箱
	for (MetalBox* metalBox : metalBox_) {
		metalBox->Draw();
	}

	// 氷
	for (IceBox* iceBox : iceBox_) {
		iceBox->Draw();
	}

	// tv
	for (TvBox* tvBox : tvBox_) {
		tvBox->Draw();
	}

	// クリア
	if (isClear_) {
		clear_->Draw();
	}

	// ゲームオーバー
	if (isGameOver_) {
		gameOver_->Draw();
	}

	// ポーズ
	if (isPause_) {
		pause_->Draw();
	}

	// ヒットエフェクト
	if(hitEffect_){
		hitEffect_->Draw();
	}

	// デバッグテキスト
	#ifdef _DEBUG
	Novice::ScreenPrintf(0, 60, "clearCount:%d", clearCount_);
	Novice::ScreenPrintf(0, 80, "playCount:%d", playCount_);
	Novice::ScreenPrintf(0, 140, "time:%d", timeLimit_);
	Novice::ScreenPrintf(0, 160, "inGameOverCount:%d", inGameOverCount_);
	#endif // _DEBUG

}
