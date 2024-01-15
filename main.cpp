#include <Novice.h>
#include "myStructs.h"
#include "Object.h"
#include "Player.h"
#include "Backround.h"
#include "MapTip.h"

const char kWindowTitle[] = "GC1C_07_コーテスジャレッドアレン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int scene = gameStage1;

	Player* player = new Player();
	Backround* haikei1 = new Backround();

	Maptip maptip = { 0 };
	initializeMaptip(maptip);
	initializeMap(maptip.map1, maptip.map2, maptip.map3);

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

		switch (scene) {
		case gameTitle:
			break; //gameTitle
		case gameColorSelect:
			break; //gameColorSelect
		case gameStage1:

			player->MovePlayer(keys, preKeys, maptip.map1);
			player->Update();

			haikei1->Draw();
			DrawMaptip(maptip.map1, maptip.imgBlock);

			player->ToScreen();
			player->Draw();
			Novice::ScreenPrintf(10, 10, "pos_.x: %f", player->pos_.x);

			break; //gameStage1
		case gameOver:
			break; //gameOver
		} //switch

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	player->~Player();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
