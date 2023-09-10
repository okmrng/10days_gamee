#include "GameOver.h"

void GameOver::Initialize()
{
	// 背景
	backgroundColor_ = 0x00000000;
	backgroundAlpha_ = 0x00000000;

	// FAILED
	failedTexture_ = Novice::LoadTexture("./resource/sprite/failed.png");
	color_ = 0xffffff00;
	alpha_ = 0x00000000;
}

void GameOver::Update(char* keys, char* preKeys)
{
	keys;
	preKeys;
	// 背景
	// フェードイン
	backgroundAlpha_ = FadeIn(backgroundAlpha_, 0x00000002, 0x000000f0);

	//FAILED
	// フェードイン
	alpha_ = FadeIn(alpha_, 0x00000002, 0x000000ff);
}

void GameOver::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, backgroundColor_ + backgroundAlpha_, kFillModeSolid);

	// FAILED
	Novice::DrawSprite(494, 250, failedTexture_, 1, 1, 0.0f, color_ + alpha_);

	#ifdef _DEBUG
	Novice::ScreenPrintf(0, 100, "GAMEOVER");
	#endif // _DEBUG

}
