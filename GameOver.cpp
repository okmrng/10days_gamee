#include "GameOver.h"

void GameOver::Initialize()
{
	// FAILED
	failedTexture_ = Novice::LoadTexture("./resource/sprite/failed.png");
	color_ = 0xffff00;
	alpha_ = 0xffff04;
}

void GameOver::Update(char* keys, char* preKeys)
{
	keys;
	preKeys;
}

void GameOver::Draw()
{
	Novice::DrawSprite(494, 250, failedTexture_, 1, 1, 0.0f, WHITE);

	#ifdef _DEBUG
	Novice::ScreenPrintf(0, 100, "GAMEOVER");
	#endif // _DEBUG

}
