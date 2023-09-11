#include "Pause.h"

void Pause::Initialize()
{
	// 文字
	PPos_ = Vector2(392.5f, 100.0f);
	APos_ = Vector2(493.5f, 100.0f);
	UPos_ = Vector2(594.5f, 100.0f);
	SPos_ = Vector2(695.5f, 100.0f);
	EPos_ = Vector2(796.5f, 100.0f);
	charT_ = 0.0f;
	
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

	toPlay_ = false;
	toRetry_ = false;
	toEnemyInfo_ = false;

	toCount_ = 5;
	toCoundDown_ = false;

	pushCount_ = 5;
	choose_ = Choose::PLAY;
	
	// 背景
	color_ = 0x00000000;
	alpha_ = 0x00000000;
}

void Pause::Update(char* keys, char* preKeys)
{
	// 背景フェード
	alpha_ = FadeIn(alpha_, 0x00000010, 0x000000f0);

	--pushCount_;

	// 選択
	if (pushCount_ <= 0) {
		switch (choose_) {
		case Choose::PLAY:
			PlayUpdate(keys, preKeys);
			break;

		case Choose::RETRY:
			RetryUpdate(keys, preKeys);
			break;

		case Choose::ENEMYINFO:
			EnemyInfoUpdate(keys, preKeys);
			break;
		}
	}
}

void Pause::PlayUpdate(char* keys, char* preKeys)
{
	// フラグ切り替え
	choosePlay_ = true;
	chooseRetry_ = false;
	chooseEnemyInfo_ = false;

	// 他選択
	if (keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0) {
		choose_ = Choose::RETRY;
	}
	else if (keys[DIK_UP] && preKeys[DIK_UP] == 0) {
		choose_ = Choose::ENEMYINFO;
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toCoundDown_ = true;
	}

	if (toCoundDown_) {
		--toCount_;
		if (toCount_ <= 0) {
			toPlay_ = true;
		}
	}
}

void Pause::RetryUpdate(char* keys, char* preKeys)
{
	// フラグ切り替え
	choosePlay_ = false;
	chooseRetry_ = true;
	chooseEnemyInfo_ = false;

	// 他選択
	if (keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0) {
		choose_ = Choose::ENEMYINFO;
	}
	else if (keys[DIK_UP] && preKeys[DIK_UP] == 0) {
		choose_ = Choose::PLAY;
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toCoundDown_ = true;
	}
	if (toCoundDown_) {
		--toCount_;
		if (toCount_ <= 0) {
			toRetry_ = true;
		}
	}
}

void Pause::EnemyInfoUpdate(char* keys, char* preKeys)
{
	// フラグ切り替え
	choosePlay_ = false;
	chooseRetry_ = false;
	chooseEnemyInfo_ = true;

	// 他選択
	if (keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0) {
		choose_ = Choose::PLAY;
	}
	else if (keys[DIK_UP] && preKeys[DIK_UP] == 0) {
		choose_ = Choose::RETRY;
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toCoundDown_ = true;
	}
	if (toCoundDown_) {
		--toCount_;
		if (toCount_ <= 0) {
			toEnemyInfo_ = true;
		}
	}
}

void Pause::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, color_ + alpha_, kFillModeSolid);

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
