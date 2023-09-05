#include "Player.h"

void Player::Initialize()
{
	radius_ = 20.0f;
	pos_ = Vector2{ radius_ + 30.0f,360.0f };
	velocity_ = 5.0f;
}

void Player::Upadate(char* keys/*, char* preKeys*/)
{
	// 移動
	if (keys[DIK_DOWN]) {
		pos_.y += velocity_;
	}
	if (keys[DIK_UP]) {
		pos_.y -= velocity_;
	}

	// 範囲制限
	if (pos_.y >= 720.0f - radius_) {
		pos_.y = 720.0f - radius_;
	}
	if (pos_.y <= radius_) {
		pos_.y = radius_;
	}
}

void Player::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, BLUE, kFillModeSolid);
}
