#include <Novice.h>
#include "Title.h"
#include "StageSelect.h"
#include "Stage1.h"

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
		ENEMYINFO    // 敵情報
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

	bool beforeStage1 = false;

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

			// 敵情報へ
			if (stage1->GetToEnemyInfo()) {
				beforeStage1 = true;
				scene = Scene::ENEMYINFO;
			}
		}

		// 敵情報
		if (scene == Scene::ENEMYINFO) {

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
		if(scene==Scene::STAGE1){
			stage1->Draw();
		}

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
