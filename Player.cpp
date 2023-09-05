#include "Player.h"

Player::~Player()
{
	for (PlayerBullet* bullet : bullet_) {
		delete bullet;
	}
}

void Player::Initialize()
{
	radius_ = 20.0f;
	pos_ = Vector2{ radius_ + 30.0f,360.0f };
	velocity_ = 5.0f;

	charge_ = 0;
}

void Player::Upadate(char* keys, char* preKeys)
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

	if (keys[DIK_SPACE]) {
		if (charge_ <= 120) {
			charge_++;
		}
		if (charge_ >= 120) {
			charge_ = 120;
		}
	}

	// 弾
	// 生成
	Attack(keys, preKeys);

	// 更新
	for (PlayerBullet* bullet : bullet_) {
		bullet->Update();
	}

	// デスフラグ立ったら弾削除
	bullet_.remove_if([](PlayerBullet* bullet) {
		if (bullet->GetIsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

void Player::Attack(char* keys, char* preKeys)
{
	if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
		// 弾の速度
		float velocity = 0;
		if (charge_ < 30) {
			velocity = 4;
		}
		if ((charge_ >= 30) && (charge_ < 60)) {
			velocity = 8;
		}
		if ((charge_ >= 60) && (charge_ < 90)) {
			velocity = 12;
		}
		if ((charge_ >= 90) && (charge_ < 120)) {
			velocity = 16;
		}
		if (charge_ >= 120) {
			velocity = 20;
		}

		// 弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(pos_, velocity);
		bullet_.push_back(newBullet);

		// チャージ量リセット
		charge_ = 0;
	}
}

void Player::Draw()
{
	// 弾
	for (PlayerBullet* bullet : bullet_) {
		bullet->Draw();
	}

	// 自機
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, BLUE, kFillModeSolid);

	Novice::ScreenPrintf(0, 0, "charge:%d", charge_);
}
