#include "Clear.h"

void Clear::Draw()
{
	// デバッグテキスト
	#ifdef _DEBUG
	Novice::ScreenPrintf(0, 80, "Clear");
	#endif // _DEBUG
}
