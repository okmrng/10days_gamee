#include "StageSelect.h"

StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
}

void StageSelect::Initiallize()
{
	toNext_ = false;

	pushCount_ = 5;
}

void StageSelect::Update(char* keys, char* preKeys)
{
	if (--pushCount_ <= 0) {
		if(keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			toNext_ = true;
		}
	}
}

void StageSelect::Draw()
{
	Novice::ScreenPrintf(0, 0, "StageSelect");
}
