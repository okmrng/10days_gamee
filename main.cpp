#include <Novice.h>
#include "Title.h"
#include "StageSelect.h"
#include "Stage1.h"
#include "EnemyInfo.h"

const char kWindowTitle[] = "10days_game";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// シーン列挙体
	enum class Scene {
		TITLE,		 // タイトル
		STGAESELECT, // ステージセレクト
		STAGE1,		 // ステージ1
		STAGE1LOAD,  // ステージ1初期化
		ENEMYINFO,   // 敵情報
		INITIALIZE   // 初期化
	};
	Scene scene = Scene::STAGE1;

	// タイトル
	Title* title = new Title();
	title->Initialize();

	// ステージセレクト
	StageSelect* stageSelect = new StageSelect();
	stageSelect->Initiallize();

	// ステージ1
	Stage1* stage1 = new Stage1();
	stage1->Initialize();

	// ステージがいくつか
	Scene beforeStage = Scene::STAGE1;

	// 敵情報
	EnemyInfo* enemyInfo = new EnemyInfo();
	enemyInfo->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// タイトル
		if (scene == Scene::TITLE) {
			title->Update(keys);
			enemyInfo->SetToBack(false);

			// 次のシーンへ
			if (title->GetToNext()) {
				scene = Scene::STGAESELECT;
			}
		}

		// ステージセレクト
		if (scene == Scene::STGAESELECT) {
			stageSelect->Update(keys);

			// 次のシーンへ
			if (stageSelect->GetToNext()) {
				scene = Scene::STAGE1LOAD;
			}
		}

		// ステージ1初期化
		if (scene == Scene::STAGE1LOAD) {
			stage1->Initialize();
			scene = Scene::STAGE1;
		}

		// ステージ1
		if(scene==Scene::STAGE1){
			stage1->Update(keys, preKeys);
			
			if (stage1->GetPause()->GetToEnemyInfo() == false) {
				enemyInfo->Initialize();
			}
			// 敵情報へ
			if (stage1->GetPause()->GetToEnemyInfo()) {
				beforeStage = Scene::STAGE1;
				scene = Scene::ENEMYINFO;
			}
		}

		// 敵情報
		if (scene == Scene::ENEMYINFO) {
			enemyInfo->Update(keys, preKeys);
			stage1->GetPause()->SetToPlay(true);

			// 戻る
			if (enemyInfo->GetToBack()) {
				switch (beforeStage)
				{
				case Scene::STAGE1:
					scene = Scene::STAGE1;
					break;
				}
			}
		}

		// 初期化
		if (scene == Scene::INITIALIZE) {
			//enemyInfo->Initialize();
			
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// タイトル
		if (scene == Scene::TITLE) {
			title->Draw();
		}

		// ステージセレクト
		if (scene == Scene::STGAESELECT) {
			stageSelect->Draw();
		}

		// ステージ1
		if(scene == Scene::STAGE1){
			stage1->Draw();
		}

		// 敵情報
		if (scene == Scene::ENEMYINFO) {
			enemyInfo->Draw();
		}

#ifdef _DEBUG
		if (stage1->GetPause()->GetToEnemyInfo()) {
			Novice::ScreenPrintf(0, 500, "true");
		}
		else { Novice::ScreenPrintf(0, 500, "false"); }
		if (enemyInfo->GetToBack()) {
			Novice::ScreenPrintf(0, 520, "true");
		}
		else { Novice::ScreenPrintf(0, 520, "false"); }
#endif // _DEBUG

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// 解放
	delete title;
	delete stageSelect;
	delete stage1;
	delete enemyInfo;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
