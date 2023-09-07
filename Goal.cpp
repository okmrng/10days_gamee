#include "Goal.h"

void Goal::Initialize(float posY)
{
	pos_ = Vector2{ 1000.0f,posY };
	size_ = Vector2{ 50.0f,50.0f };
	collisionP_ = Vector2{ 38.0f,38.0f };
	collisionPos_ = pos_ + collisionP_;
	collisionSize_ = size_ / 2;
}

void Goal::Draw()
{
	Novice::DrawBox(int(pos_.x + 25), int(pos_.y + 25), int(size_.x), int(size_.y), 0.0f, 
		GREEN, kFillModeWireFrame);

#ifdef _DEBUG
	Novice::DrawBox(int(collisionPos_.x), int(collisionPos_.y), int(collisionSize_.x), int(collisionSize_.y), 0.0f,
		GREEN, kFillModeWireFrame);
#endif // _DEBUG
}
