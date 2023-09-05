#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector2 pos, float velocity)
{
	radius_ = 10.0f;
	pos_ = pos;
	velocity_ = velocity;
	collisionPos_ = pos_;
	size_ = Vector2(20.0f, 20.0f);
	isDead_ = false;
}

void PlayerBullet::Update()
{
	// 移動
	pos_.x += velocity_;

	// 当たり判定用の座標
	collisionPos_ = pos_ - radius_;

	// デス
	if (pos_.x >= 1280.0f + radius_) {
		isDead_ = true;
	}
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

void PlayerBullet::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, RED, kFillModeSolid);

	// 当たり判定チェック用
	Novice::DrawBox(int(collisionPos_.x), int(collisionPos_.y), int(size_.x), int(size_.y), 0.0f, WHITE, kFillModeWireFrame);
}
