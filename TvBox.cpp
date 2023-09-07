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
	count_ = 3;
	texture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");
	texture0_ = Novice::LoadTexture("./resource/sprite/tv-count_0.png");
	texture1_ = Novice::LoadTexture("./resource/sprite/tv-count_1.png");
	texture2_ = Novice::LoadTexture("./resource/sprite/tv-count_2.png");
	texture3_ = Novice::LoadTexture("./resource/sprite/tv-count_3.png");

	// ゴール
	goal_ = new Goal();
	goal_->Initialize(pos_.y);
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

	// カウントが0になったら0で固定
	if (count_ <= 0) {
		count_ = 0;
	}
}

void TvBox::OnCollision()
{
	hit_ = true;
	stop_ = false;
	player_->SetIsBullet(false);
	count_ -= 1;
}

void TvBox::Draw()
{
	// ゴール
	goal_->Draw();

	// 本体
	Novice::DrawSprite(int(pos_.x), int(pos_.y), texture_, 1, 1, 0.0f, WHITE);

	// カウント
	if(count_ == 3){
		Novice::DrawSprite(int(pos_.x + 25), int(pos_.y + 15), texture3_, 1, 1, 0.0f, WHITE);
	}
	else if (count_ == 2) {
		Novice::DrawSprite(int(pos_.x + 25), int(pos_.y + 15), texture2_, 1, 1, 0.0f, WHITE);
	}
	if (count_ == 1) {
		Novice::DrawSprite(int(pos_.x + 25), int(pos_.y + 15), texture1_, 1, 1, 0.0f, WHITE);
	}
	if (count_ == 0) {
		Novice::DrawSprite(int(pos_.x + 25), int(pos_.y + 15), texture0_, 1, 1, 0.0f, WHITE);
	}
}
