#include "Player.h"

Player::Player()
{
	bullet_ = nullptr;
}

Player::~Player()
{
	delete bullet_;
}

void Player::Initialize()
{
	radius_ = 20.0f;
	pos_ = Vector2{ radius_ + 30.0f,360.0f };
	velocity_ = 5.0f;
	color_ = BLUE;
	texture_ = Novice::LoadTexture("./resource/sprite/player.png");

	charge_ = 0;
	power_ = 0;
	canShoot_ = 0;
	isBullet_ = true;
}

void Player::Update(char* keys, char* preKeys)
{
	// 移動
	if (keys[DIK_DOWN]) {
		pos_.y += velocity_;
	}
	if (keys[DIK_UP]) {
		pos_.y -= velocity_;
	}

	// 範囲制限
	if (pos_.y >= 670.0f) {
		pos_.y = 670.0f;
	}
	if (pos_.y <= radius_ + 5) {
		pos_.y = radius_ + 5;
	}

	if (!bullet_) {
		if (keys[DIK_SPACE]) {
			if (charge_ <= 120) {
				charge_++;
			}
			if (charge_ >= 120) {
				charge_ = 120;
			}
		}
	}

	// パワーによって自機の色を変化
	if (charge_ < 30) {
		color_ = BLUE;
	}
	else if ((charge_ >= 30) && (charge_ < 60)) {
		color_ = 0x00bfff;
	}
	else if ((charge_ >= 60) && (charge_ < 90)) {
		color_ = 0x87cefa;
	}
	else if ((charge_ >= 90) && (charge_ < 120)) {
		color_ = 0xafeeee;
	}
	else if (charge_ >= 120) {
		color_ = WHITE;
	}

	// 弾
	// 生成
	if (canShoot_ > 0) {
		Attack(keys, preKeys);
	}

	// 更新
	if (bullet_) {
		bullet_->Update();
	}

	// デスフラグ立ったら弾削除
	if (bullet_) {
		if (bullet_->GetIsDead()) {
			delete bullet_;
			bullet_ = nullptr;
		}
	}

	// 弾が撃てなくなった後にチャージリセット
	if (canShoot_ <= 0) {
		charge_ = 0;
	}
}

void Player::Attack(char* keys, char* preKeys)
{
	if (!bullet_) {
		if (isBullet_) {
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				// パワー
				if (charge_ < 30) {
					power_ = 1;
					color_ = 0x1e90ff;
				}
				else if ((charge_ >= 30) && (charge_ < 60)) {
					power_ = 2;
					color_ = 0x00bfff;
				}
				else if ((charge_ >= 60) && (charge_ < 90)) {
					power_ = 3;
					color_ = 0x87cefa;
				}
				else if ((charge_ >= 90) && (charge_ < 120)) {
					power_ = 4;
					color_ = 0xafeeee;
				}
				else if (charge_ >= 120) {
					power_ = 5;
					color_ = WHITE;
				}

				// 弾の生成と初期化
				PlayerBullet* newBullet = new PlayerBullet();
				newBullet->Initialize(pos_, power_);
				bullet_ = newBullet;

				// チャージ量リセット
				charge_ = 0;

				// 弾が撃てる数を減らす
				canShoot_ -= 1;
			}
		}
	}
}

void Player::BulletOnCollision()
{
	bullet_->OnCollision();
}

void Player::Draw(bool gameOver)
{
	// 弾
	if (bullet_) {
		if(!gameOver){
			bullet_->Draw();
		}
	}

	// 自機
	Novice::DrawSprite(int(pos_.x - 55), int(pos_.y - 33), texture_, 0.5, 0.5, 0.0f, WHITE);

	// デバッグ用
#ifdef _DEBUG
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, color_, kFillModeWireFrame);

	Novice::ScreenPrintf(0, 0, "charge:%d", charge_);
	Novice::ScreenPrintf(0, 20, "canShoot:%d", canShoot_);
	Novice::ScreenPrintf(0, 180, "power:%d", power_);
	Novice::ScreenPrintf(0, 200, "bulletPower:%d", GetBulletPower());
	if (bullet_) {
		Novice::ScreenPrintf(0, 460, "bullet:true");
	}else{ Novice::ScreenPrintf(0, 460, "bullet:false"); }
#endif // _DEBUG
}

Vector2 Player::GetBulletCollisionPos()
{
	if (bullet_) {
		return bullet_->GetCollisionPos();
	}
	else { return { -1000,-1000 }; }
}

Vector2 Player::GetBulletSize()
{
	if (bullet_) {
		return bullet_->GetSize();
	}
	else { return { 0,0 }; }
}

int32_t Player::GetBulletPower()
{
	if(bullet_){
		return bullet_->GetPower();
	}
	else{ return 0; }
}

bool Player::GetBulletIsDead()
{
	if (bullet_) {
		return bullet_->GetIsDead();
	}
	else { return 0; }
}
