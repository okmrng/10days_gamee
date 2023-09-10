#include "EnemyInfo.h"

EnemyInfo::EnemyInfo()
{
}

EnemyInfo::~EnemyInfo()
{
}

void EnemyInfo::Initialize()
{
	woodTexture_ = Novice::LoadTexture("./resource/sprite/wood-Box.png");
	metalTexture_ = Novice::LoadTexture("./resource/sprite/metal-Box.png");
	iceTexture_ = Novice::LoadTexture("./resource/sprite/ice-Box.png");
	tvTexture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");

	// UI
	choosePos_ = Vector2(292.5f, 133.0f);
	chooseT_ = 0.0f;
	chooseTexture_ = Novice::LoadTexture("./resource/UI/chooseEnemy.png");
	onEaseWood_ = false;
	onEaseMetal_ = false;
	onEaseIce_ = false;
	onEaseTv_ = false;

	toWood_ = false;
	toMetal_ = false;
	toIce_ = false;
	toTv_ = false;

	toBack_ = false;

	pushCount_ = 5;
	canPush_ = true;

	choose_ = Choose::WOOD;
}

void EnemyInfo::Update(char* keys, char* preKeys)
{
	if (--pushCount_ <= 0) {
		if (keys[DIK_BACKSPACE] && preKeys[DIK_BACKSPACE] == 0) {
			toBack_ = true;
		}

		switch (choose_)
		{
		case EnemyInfo::Choose::WOOD:
			WoodUpdate(keys, preKeys);
			break;
		case EnemyInfo::Choose::METAL:
			MetalUpdate(keys, preKeys);
			break;
		case EnemyInfo::Choose::ICE:
			IceUpdate(keys, preKeys);
			break;
		case EnemyInfo::Choose::TV:
			TvUpdate(keys, preKeys);
			break;
		default:
			break;
		}
	}
}

void EnemyInfo::WoodUpdate(char* keys, char* preKeys)
{
	onEaseWood_ = false;

	// 他選択
	if (canPush_) {
		if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0) {
			canPush_ = false;
			onEaseIce_ = true;
		}
		if (keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0) {
			canPush_ = false;
			onEaseMetal_ = true;
		}
	}

	// イージング
	if (onEaseIce_ == true || onEaseMetal_ == true || onEaseTv_ == true) {
		if (chooseT_ < 1.0f) {
			chooseT_ += 1.0f / 30.0f;
		}
		if (chooseT_ >= 1.0f) {
			chooseT_ = 1.0f;
		}
	}
	else { chooseT_ = 0.0f; }
	if (onEaseIce_) {
		choosePos_.x = EaseOutCirc(292.5f, 792.5f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::ICE;
		}
	}
	if (onEaseMetal_) {
		choosePos_.y = EaseOutCirc(133.0f, 433.0f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::METAL;
		}
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toWood_ = true;
	}
}

void EnemyInfo::MetalUpdate(char* keys, char* preKeys)
{
	onEaseMetal_ = false;

	// 他選択
	if (canPush_) {
		if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == 0) {
			onEaseTv_ = true;
			canPush_ = false;
		}
		if (keys[DIK_UP] && preKeys[DIK_UP] == 0) {
			onEaseWood_ = true;
			canPush_ = false;
		}
	}

	// イージング
	if (onEaseIce_ == true || onEaseWood_ == true || onEaseTv_ == true) {
		if (chooseT_ < 1.0f) {
			chooseT_ += 1.0f / 30.0f;
		}
		if (chooseT_ >= 1.0f) {
			chooseT_ = 1.0f;
		}
	}
	else { chooseT_ = 0.0f; }
	if (onEaseWood_) {
		choosePos_.y = EaseOutCirc(433.0f, 133.0f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::WOOD;
		}
	}
	if (onEaseTv_) {
		choosePos_.x = EaseOutCirc(292.5f, 792.5f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::TV;
		}
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toMetal_ = true;
	}
}

void EnemyInfo::IceUpdate(char* keys, char* preKeys)
{
	onEaseIce_ = false;

	// 他選択
	if (canPush_) {
		if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0) {
			onEaseWood_ = true;
			canPush_ = false;
		}
		if (keys[DIK_DOWN] && preKeys[DIK_DOWN] == 0) {
			onEaseTv_ = true;
			canPush_ = false;
		}
	}

	// イージング
	if (onEaseWood_ == true || onEaseMetal_ == true || onEaseTv_ == true) {
		if (chooseT_ < 1.0f) {
			chooseT_ += 1.0f / 30.0f;
		}
		if (chooseT_ >= 1.0f) {
			chooseT_ = 1.0f;
		}
	}
	else { chooseT_ = 0.0f; }
	if (onEaseWood_) {
		choosePos_.x = EaseOutCirc(792.5f, 292.5f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::WOOD;
		}
	}
	if (onEaseTv_) {
		choosePos_.y = EaseOutCirc(133.0f, 433.0f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::TV;
		}
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toIce_ = true;
	}
}

void EnemyInfo::TvUpdate(char* keys, char* preKeys)
{
	onEaseTv_ = false;

	// 他選択
	if (canPush_) {
		if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == 0) {
			onEaseMetal_ = true;
			canPush_ = false;
		}
		if (keys[DIK_UP] && preKeys[DIK_UP] == 0) {
			onEaseIce_ = true;
			canPush_ = false;
		}
	}

	// イージング
	if (onEaseIce_ == true || onEaseWood_ == true || onEaseMetal_ == true) {
		if (chooseT_ < 1.0f) {
			chooseT_ += 1.0f / 30.0f;
		}
		if (chooseT_ >= 1.0f) {
			chooseT_ = 1.0f;
		}
	}
	else { chooseT_ = 0.0f; }
	if (onEaseIce_) {
		choosePos_.y = EaseOutCirc(433.0f, 133.0f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::ICE;
		}
	}
	if (onEaseMetal_) {
		choosePos_.x = EaseOutCirc(792.5f, 292.5f, chooseT_);
		if (chooseT_ >= 1.0f) {
			canPush_ = true;
			choose_ = Choose::METAL;
		}
	}

	// 実行
	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
		toTv_ = true;
	}
}

void EnemyInfo::Draw()
{
	// 木箱
	Novice::DrawSprite(320, 160, woodTexture_, 1, 1, 0.0f, WHITE);
	// 金属製の箱
	Novice::DrawSprite(320, 460, metalTexture_, 1, 1, 0.0f, WHITE);
	// 氷
	Novice::DrawSprite(820, 160, iceTexture_, 1, 1, 0.0f, WHITE);
	// tv
	Novice::DrawSprite(820, 460, tvTexture_, 1, 1, 0.0f, WHITE);

	// UI
	Novice::DrawSprite(int(choosePos_.x), int(choosePos_.y), chooseTexture_, 1, 1, 0.0f, WHITE);

#ifdef _DEBUG
	if (onEaseIce_) {
		Novice::ScreenPrintf(0, 0, "true");
	}else{ Novice::ScreenPrintf(0, 0, "false"); }
	Novice::ScreenPrintf(0, 20, "t:%f", chooseT_);
#endif // _DEBUG

}
