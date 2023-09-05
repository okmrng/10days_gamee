#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	delete player_;
}

void Stage1::Initialize()
{
	// 自機
	player_ = new Player();
	player_->Initialize();
}

void Stage1::Update(char* keys, char* preKeys)
{
	// 自機
	player_->Upadate(keys, preKeys);
}

void Stage1::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	// 自機
	player_->Draw();
}
