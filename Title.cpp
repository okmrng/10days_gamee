#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	// 画像
	texture_ = Novice::LoadTexture("./resource/background/title.png");
	color_ = 0xffffff;
	alpha_ = 0x000002;
	isFade_ = false;

	// シーン遷移
	nextCount_ = 45;
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
	if (color_ <= 0xffff00) {
		color_ = 0xffff00;
		if(--nextCount_<=0){
			toNext_ = true;
		}
	}
}

void Title::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
	Novice::DrawSprite(0, 0, texture_, 1, 1, 0.0f, color_);
}
