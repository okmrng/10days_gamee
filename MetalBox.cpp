#include "MetalBox.h"

#include "Player.h"

void MetalBox::Initialize(Vector2 pos, Vector2 size)
{
	// 本体
	pos_ = pos;
	size_ = size;
	velocity_ = 0;
	acceleration_ = 2;
	hit_ = false;
	stop_ = false;
	texture_ = Novice::LoadTexture("./resource/sprite/metal-Box.png");
	startPoint_ = pos_.x;
	isGoal_ = false;
	t_ = 0.0f;

	// ゴール
	goal_ = new Goal();
	goal_->Initialize(pos_.y);
	addStop_ = false;
}

void MetalBox::Update()
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

	// ゴールするまで始点を箱の座標に合わせる
	if (!isGoal_) {
		startPoint_ = pos_.x;
	}

	// ゴールしたらゴールにイージング
	if (isGoal_) {
		if (t_ < 1.0f) {
			t_ += 1.0f / 30.0f;
		}
		if (t_ >= 1.0f) {
			t_ = 1.0f;
		}

		float easedT_ = sqrt(1.0f - pow(t_ - 1.0f, 2.0f));

		pos_.x = (1.0f - easedT_) * startPoint_ + easedT_ * (goal_->GetPos().x);
	}
}

void MetalBox::OnCollision()
{
	hit_ = true;
	stop_ = false;
	player_->SetIsBullet(false);
}

void MetalBox::IsGoal()
{
	isGoal_ = true;
	addStop_ = true;
}

void MetalBox::Draw()
{
	// ゴール
	goal_->Draw();

	// 本体
	Novice::DrawSprite(int(pos_.x), int(pos_.y), texture_, 1, 1, 0.0f, WHITE);
}
