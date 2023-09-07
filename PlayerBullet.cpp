#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector2 pos, int32_t power)
{
	radius_ = 10.0f;
	pos_ = pos;
	velocity_ = 10.0f;
	collisionPos_ = pos_;
	size_ = Vector2(68.0f, 60.0f);
	isDead_ = false;
	power_ = power;
	texture_ = Novice::LoadTexture("./resource/sprite/fist.png");
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
	Novice::DrawSprite(int(pos_.x - 90), int(pos_.y - 30), texture_, 1, 1, 0.0f, WHITE);

	// デバッグ用
	#ifdef _DEBUG
	// 当たり判定チェック用
	Novice::DrawBox(int(collisionPos_.x), int(collisionPos_.y), int(size_.x), int(size_.y), 
		0.0f, RED, kFillModeWireFrame);
	#endif // _DEBUG
}
