#include "TvInfo.h"

TvInfo::TvInfo()
{
}

TvInfo::~TvInfo()
{
}

void TvInfo::Initialize()
{
	// tv
	pos_ = Vector2(100.0f, 240.0f);
	theta_ = 0.0f;
	tvTexture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");

	// 説明
	infoTexture_ = Novice::LoadTexture("./resource/sprite/tvInfo.png");

	toBack_ = false;
}

void TvInfo::Update(char* keys, char* preKeys)
{
	pos_.y = sinf(theta_) * 20.0f + 240.0f;
	theta_ += (float)M_PI / 120.0f;

	// 戻る
	if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
		toBack_ = true;
	}
}

void TvInfo::Draw()
{
	// tv
	Novice::DrawSprite(int(pos_.x), int(pos_.y), tvTexture_, 2, 2, 0.0f, WHITE);

	// 説明
	Novice::DrawSprite(400, 28, infoTexture_, 1, 1, 0.0f, WHITE);
}
