#include "TvBox.h"

#include "Player.h"

void TvBox::Initialize(Vector2 pos, Vector2 size)
{
	pos_ = pos;
	size_ = size;
	velocity_ = 0;
	acceleration_ = 1;
	hit_ = false;
	stop_ = false;
	texture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");
}

void TvBox::Update()
{
	// パワーによって速度を変える
	if (player_->GetBulletPower() == 1) {
		velocity_ = 10;
	}
	else if (player_->GetBulletPower() == 2) {
		velocity_ = 15;
	}
	else if (player_->GetBulletPower() == 3) {
		velocity_ = 20;
	}
	else if (player_->GetBulletPower() == 4) {
		velocity_ = 25;
	}
	else if (player_->GetBulletPower() == 5) {
		velocity_ = 30;
	}

	// 当たった時の処理
	if (hit_) {
		// 徐々に減速させる
		velocity_ -= acceleration_;
		if (velocity_ <= 0) {
			velocity_ = 0;

			stop_ = true;

			player_->SetIsBullet(true);
		}

		// 移動
		if (!stop_) {
			pos_.x += velocity_;
		}

	}
}

void TvBox::OnCollision()
{
	hit_ = true;
	stop_ = false;
	player_->SetIsBullet(false);
}

void TvBox::Draw()
{
	Novice::DrawSprite(int(pos_.x), int(pos_.y), texture_, 1, 1, 0.0f, WHITE);
}
