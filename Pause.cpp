#include "Pause.h"

void Pause::Initialize()
{
	// 文字
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

	// UI
	playPos_ = Vector2(528.0f, 271.0f);
	retryPos_ = Vector2(505.5f, 375.0f);
	enemyInfoPos_ = Vector2(414.0f, 479.0f);

	playTexture_ = Novice::LoadTexture("./resource/UI/play.png");
	retryTexture_ = Novice::LoadTexture("./resource/UI/retry.png");
	enemyInfoTexture_ = Novice::LoadTexture("./resource/UI/enemyInfo.png");
	choosePlayTexture_ = Novice::LoadTexture("./resource/UI/play_choose.png");
	chooseRetryTexture_ = Novice::LoadTexture("./resource/UI/retry_choose.png");
	chooseEnemyInfoTexture_ = Novice::LoadTexture("./resource/UI/enemyInfo_choose.png");

	choosePlay_ = false;
	chooseRetry_ = false;
	chooseEnemyInfo_ = false;
}

void Pause::Draw()
{
	// 文字
	Novice::DrawSprite(int(PPos_.x), int(PPos_.y), PTexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(APos_.x), int(APos_.y), ATexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(UPos_.x), int(UPos_.y), UTexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(SPos_.x), int(SPos_.y), STexture_, 1, 1, 0.0f, WHITE);
	Novice::DrawSprite(int(EPos_.x), int(EPos_.y), ETexture_, 1, 1, 0.0f, WHITE);

	// UI
	if (!choosePlay_) {
		Novice::DrawSprite(int(playPos_.x), int(playPos_.y), playTexture_, 1, 1, 0.0f, WHITE);
	}
	else if (choosePlay_) {
		Novice::DrawSprite(int(playPos_.x), int(playPos_.y), choosePlayTexture_, 1, 1, 0.0f, WHITE);
	}

	if (!chooseRetry_) {
		Novice::DrawSprite(int(retryPos_.x), int(retryPos_.y), retryTexture_, 1, 1, 0.0f, WHITE);
	}
	else if (chooseRetry_) {
		Novice::DrawSprite(int(retryPos_.x), int(retryPos_.y), chooseRetryTexture_, 1, 1, 0.0f, WHITE);
	}

	if (!chooseEnemyInfo_) {
		Novice::DrawSprite(int(enemyInfoPos_.x), int(enemyInfoPos_.y), enemyInfoTexture_, 1, 1, 0.0f, WHITE);
	}
	else if (chooseEnemyInfo_) {
		Novice::DrawSprite(int(enemyInfoPos_.x), int(enemyInfoPos_.y), chooseEnemyInfoTexture_, 1, 1, 0.0f, WHITE);
	}
}
