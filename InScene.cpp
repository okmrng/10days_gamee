#include "InScene.h"

void InScene::Initialize()
{
	// 弾
	fistPosX_ = -1311.0f;
	t_ = 0.0f;
	fistTexture_ = Novice::LoadTexture("./resource/sprite/scene_fist.png");

	// 黒
	blackPosX_ = 0.0f;
}

void InScene::Update()
{
	// イージング
	if (t_ < 1.0f) {
		t_ += 1.0f /120.0f;
	}
	if (t_ >= 1.0f) {
		t_ = 1.0f;
	}
	fistPosX_ = EaseOutCirc(-875.0f, 2155.0f, t_);
	blackPosX_ = EaseOutCirc(0.0f, 3030.0f, t_);
}

void InScene::Draw()
{
	// 弾
	Novice::DrawSprite(int(fistPosX_), 115, fistTexture_, 1, 1, 0.0f, WHITE);

	// 黒
	Novice::DrawBox(int(blackPosX_), 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
}
