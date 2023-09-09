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
	metalTexture_ = Novice::LoadTexture("./resource/sprite/ice-Box.png");
	metalTexture_ = Novice::LoadTexture("./resource/sprite/tv-Box.png");
}

void EnemyInfo::Update(char* keys, char* preKeys)
{
}

void EnemyInfo::Draw()
{
	// 木箱
	Novice::DrawSprite(200, 200, woodTexture_, 1, 1, 0.0f, WHITE);
	// 金属製の箱
	Novice::DrawSprite(200, 520, metalTexture_, 1, 1, 0.0f, WHITE);
	// 氷
	Novice::DrawSprite(800, 200, iceTexture_, 1, 1, 0.0f, WHITE);
	// tv
	Novice::DrawSprite(800, 520, tvTexture_, 1, 1, 0.0f, WHITE);
}
