#include "Title.h"

void Title::Initialize()
{
	// 画像
	texture_ = Novice::LoadTexture("./resource/background/title.png");
	color_ = 0xffffff;
	alpha_ = 0x000002;
	isFade_ = false;

	toNext_ = false;
}

void Title::Update(char* keys)
{
	if (keys[DIK_SPACE]) {
		isFade_ = true;
	}

	// フェードアウト
	if (isFade_) {
		color_ -= alpha_;
	}

	// フェードアウトしきったら次のシーンへ
	if (color_ <= 0x000000) {
		toNext_ = true;
	}
}

void Title::Draw()
{
	Novice::DrawSprite(0, 0, texture_, 1, 1, 0.0f, color_);
}
