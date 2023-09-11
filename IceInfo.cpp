﻿#include "IceInfo.h"

IceInfo::IceInfo()
{
}

IceInfo::~IceInfo()
{
}

void IceInfo::Initialize()
{
	// 氷
	pos_ = Vector2(100.0f, 240.0f);
	theta_ = 0.0f;
	iceTexture_ = Novice::LoadTexture("./resource/sprite/ice-Box.png");

	// 説明
	infoTexture_ = Novice::LoadTexture("./resource/sprite/iceInfo.png");

	toBack_ = false;

	// シーン遷移演出
	inScene_ = new InScene();
	inScene_->Initialize();

	outScene_ = new OutScene();
	outScene_->Initialize();
	toOutScene_ = false;
}

void IceInfo::Update(char* keys, char* preKeys)
{
	// シーン遷移演出
	inScene_->Update();

	if (toOutScene_) {
		outScene_->Update();
	}
	if (outScene_->GetToNext()) {
		toBack_ = true;
	}

	pos_.y = sinf(theta_) * 20.0f + 240.0f;
	theta_ += (float)M_PI / 120.0f;

	// 戻る
	if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
		toOutScene_ = true;
	}
}

void IceInfo::Draw()
{
	// 氷
	Novice::DrawSprite(int(pos_.x), int(pos_.y), iceTexture_, 2, 2, 0.0f, WHITE);

	// 説明
	Novice::DrawSprite(400, int(152.5), infoTexture_, 1, 1, 0.0f, WHITE);

	// シーン遷移演出
	inScene_->Draw();

	outScene_->Draw();
}
