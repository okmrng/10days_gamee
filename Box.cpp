#include "Box.h"

void Box::Initialize(Vector2 pos, Vector2 size)
{
	pos_ = pos;
	size_ = size;
	velocity_ = 0;
}

void Box::Update()
{

}

void Box::OnCollision()
{

}

void Box::Draw()
{
	Novice::DrawBox(int(pos_.x), int(pos_.y), int(size_.x), int(size_.y), 0.0f, GREEN, kFillModeSolid);
}
