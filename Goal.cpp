#include "Goal.h"

void Goal::Initialize(float posY)
{
	pos_ = Vector2{ 1000.0f,posY };
	size_ = Vector2{ 100.0f,100.0f };
}

void Goal::Draw()
{
	Novice::DrawBox(int(pos_.x), int(pos_.y), int(size_.x), int(size_.y), 0.0f, GREEN, kFillModeWireFrame);
}
