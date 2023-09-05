#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector2 pos)
{
	radius_ = 10.0f;
	pos_ = pos;
	velocity_ = 20.0f;
	isDead_ = false;
}

void PlayerBullet::Update()
{
	// 移動
	pos_.x += velocity_;
}

void PlayerBullet::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, RED, kFillModeSolid);
}
