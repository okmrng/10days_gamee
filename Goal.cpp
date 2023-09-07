#include "Goal.h"

void Goal::Initialize(float posY)
{
	pos_ = Vector2{ 1000.0f,posY };
	size_ = Vector2{ 50.0f,50.0f };
}

void Goal::Draw()
{
	Novice::DrawBox(int(pos_.x + 25), int(pos_.y + 25), int(size_.x), int(size_.y), 0.0f, 
		GREEN, kFillModeWireFrame);
}
