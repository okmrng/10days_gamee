#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector2 pos, float velocity)
{
	radius_ = 10.0f;
	pos_ = pos;
	velocity_ = velocity;
	isDead_ = false;
}

void PlayerBullet::Update()
{
	// 移動
	pos_.x += velocity_;

	// デス
	if (pos_.x >= 1280.0f + radius_) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, RED, kFillModeSolid);
}
