﻿#include "WoodInfo.h"

WoodInfo::WoodInfo()
{
}

WoodInfo::~WoodInfo()
{
}

void WoodInfo::Initialize()
{
	// 木箱
	pos_ = Vector2(100.0f, 240.0f);
	theta_ = 0.0f;
	woodTexture_ = Novice::LoadTexture("./resource/sprite/wood-Box.png");

	// 説明
	infoTexture_ = Novice::LoadTexture("./resource/sprite/woodInfo.png");

	toBack_ = false;
}

void WoodInfo::Update(char* keys, char* preKeys)
{
	pos_.y = sinf(theta_) * 20.0f + 240.0f;
	theta_ += (float)M_PI / 120.0f;

	// 戻る
	if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
		toBack_ = true;
	}
}

void WoodInfo::Draw()
{
	// 木箱
	Novice::DrawSprite(int(pos_.x), int(pos_.y), woodTexture_, 2, 2, 0.0f, WHITE);

	// 説明
	Novice::DrawSprite(400, int(220.5), infoTexture_, 1, 1, 0.0f, WHITE);
}