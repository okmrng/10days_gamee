#include "Pause.h"

void Pause::Initialize()
{
	PPos_ = Vector2(392.5f, 100.0f);
	APos_ = Vector2(493.5f, 100.0f);
	UPos_ = Vector2(594.5f, 100.0f);
	SPos_ = Vector2(695.5f, 100.0f);
	EPos_ = Vector2(796.5f, 100.0f);
	
	PTexture_ = Novice::LoadTexture("./resource/sprite/P.png");
	ATexture_ = Novice::LoadTexture("./resource/sprite/A.png");
	UTexture_ = Novice::LoadTexture("./resource/sprite/U.png");
	STexture_ = Novice::LoadTexture("./resource/sprite/S.png");
	ETexture_ = Novice::LoadTexture("./resource/sprite/E.png");
}

void Pause::Draw()
{
	// 文字
	Novice::DrawSprite(int(PPos_.x), int(PPos_.y), PTexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(APos_.x), int(APos_.y), ATexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(UPos_.x), int(UPos_.y), UTexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(SPos_.x), int(SPos_.y), STexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(EPos_.x), int(EPos_.y), ETexture_, 1, 1, 0.0f, WHITE);
}
