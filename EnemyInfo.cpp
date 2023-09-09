#include "EnemyInfo.h"

EnemyInfo::EnemyInfo()
{
}

EnemyInfo::~EnemyInfo()
{
}

void EnemyInfo::Initialize()
{
	woodTexture_ = Novice::LoadTexture("./resource/sprite/wood-Box.png");
	metalTexture_ = Novice::LoadTexture("./resource/sprite/metal-Box.png");
	iceTexture_ = Novice::LoadTexture("./resource/sprite/ice-Box.png");
	tvTexture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");

	toBack_ = false;
}

void EnemyInfo::Update(char* keys, char* preKeys)
{
	if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
		toBack_ = true;
	}
}

void EnemyInfo::Draw()
{
	// 木箱
	Novice::DrawSprite(320, 160, woodTexture_, 1, 1, 0.0f, WHITE);
	// 金属製の箱
	Novice::DrawSprite(320, 460, metalTexture_, 1, 1, 0.0f, WHITE);
	// 氷
	Novice::DrawSprite(820, 160, iceTexture_, 1, 1, 0.0f, WHITE);
	// tv
	Novice::DrawSprite(820, 460, tvTexture_, 1, 1, 0.0f, WHITE);

#ifdef _DEBUG
	if (toBack_) {
		Novice::ScreenPrintf(0, 0, "true");
	}else{ Novice::ScreenPrintf(0, 0, "false"); }
#endif // _DEBUG

}
