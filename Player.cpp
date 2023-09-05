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
	if (keys[DIK_SPACE] && (preKeys[DIK_SPACE] == 0)) {
		// 弾の生成と初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(pos_);
		bullet_.push_back(newBullet);
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
}
