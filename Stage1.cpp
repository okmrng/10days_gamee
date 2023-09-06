#include "Stage1.h"
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
}

void Stage1::Initialize()
{
	// 自機
	player_ = new Player();
	player_->Initialize(5);

	// コマンド
	LoadData("resource/csv/boxData.csv", boxPopComands_);
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
	// 自機
	player_->Upadate(keys, preKeys);

	// 箱
	UpdateBoxComands();
	// 木箱
	for (Box* box : box_) {
		box->Update();
	}

	//	金属製の箱
	for (MetalBox* metalBox : metalBox_) {
		metalBox->Update();
	}

	// 当たり判定
	CheckAllCollision();
}

void Stage1::CheckAllCollision()
{
	// 判定用の変数
	Vector2 posA, posB;   // 座標
	Vector2 sizeA, sizeB; // 幅

	// 自弾と木箱の当たり判定
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
			// 箱
			box->OnCollision();
			// 自弾
			player_->BulletOnCollision();
		}
	}
	#pragma endregion

	// 自弾と金属製の箱の当たり判定
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
			// 箱
			metalBox->OnCollision();
			// 自弾
			player_->BulletOnCollision();
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
		}
	}
}

void Stage1::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	// 自機
	player_->Draw();

	// 箱
	// 木箱
	for (Box* box : box_) {
		box->Draw();
	}

	// 金属製の箱
	for (MetalBox* metalBox : metalBox_) {
		metalBox->Draw();
	}
}
