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
		TITLE,			 // タイトル
		STGAESELECTLOAD, // ステージセレクト初期化
		STGAESELECT,	 // ステージセレクト
		STAGE1LOAD,		 // ステージ1初期化
		STAGE1,			 // ステージ1
		STAGE2LOAD,		 // ステージ2初期化
		STAGE2,			 // ステージ2
		STAGE3LOAD,		 // ステージ3初期化
		STAGE3,			 // ステージ3
		STAGE4LOAD,		 // ステージ4初期化
		STAGE4,			 // ステージ4
		STAGE5LOAD,		 // ステージ5初期化
		STAGE5,			 // ステージ5
		STAGE6LOAD,		 // ステージ6初期化
		STAGE6,			 // ステージ6
		STAGE7LOAD,		 // ステージ7初期化
		STAGE7,			 // ステージ7
		STAGE8LOAD,		 // ステージ8初期化
		STAGE8,			 // ステージ8
		ENEMYINFO,		 // 敵情報
	};
	Scene scene = Scene::STGAESELECT;

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

		// ステージセレクト初期化
		if (scene == Scene::STGAESELECTLOAD) {
			stageSelect->Initiallize();
			scene = Scene::STGAESELECT;
		}

		// ステージセレクト
		if (scene == Scene::STGAESELECT) {
			stageSelect->Update(keys, preKeys);

			// 次のシーンへ
			if (stageSelect->GetToStage1()) {
				scene = Scene::STAGE1LOAD;
			}
			if (stageSelect->GetToStage2()) {
				scene = Scene::STAGE2LOAD;
			}
			if (stageSelect->GetToStage3()) {
				scene = Scene::STAGE3LOAD;
			}
			if (stageSelect->GetToStage4()) {
				scene = Scene::STAGE4LOAD;
			}
			if (stageSelect->GetToStage5()) {
				scene = Scene::STAGE5LOAD;
			}
			if (stageSelect->GetToStage6()) {
				scene = Scene::STAGE6LOAD;
			}
			if (stageSelect->GetToStage7()) {
				scene = Scene::STAGE7LOAD;
			}
			if (stageSelect->GetToStage8()) {
				scene = Scene::STAGE8LOAD;
			}
		}

		// ステージ1初期化
		if (scene == Scene::STAGE1LOAD) {
			stage1->Retry();
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

			// ステージセレクトへ
			if (stage1->GetClear()->GetToNext() || stage1->GetGameOver()->GetToStageSelect()) {
				scene = Scene::STGAESELECTLOAD;
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
