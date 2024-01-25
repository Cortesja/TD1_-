#include <Novice.h>
#include "myStructs.h"
#include "Object.h"
#include "Player.h"
#include "Backround.h"
#include "MapTip.h"
#include "Light.h"
#include "Color.h"

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
	Light* playerLight = new Light();
	Backround* haikei1 = new Backround();

	Maptip maptip = { 0 };
	MaptipBlock block[bMapY][bMapX];

	initializeMaptip(maptip);
	initializeMap(maptip.map1, maptip.map2, maptip.map3, block);

	clock_t startingTime = clock();
	float timeElapsed = 0;

	bool night = false;
	//bool isShake = false;
	int timer = 0;

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

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				night = true;
				haikei1->night_ = true;
			}

			player->MovePlayer(keys, preKeys, maptip.map1);
			player->Update(maptip.map1, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////
			timeElapsed = getElapsedTime(startingTime);

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed, player->isHit_);
			haikei1->Draw();

			blockUpdate(timeElapsed, night, timer, block);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			DrawMaptip(maptip.map1, maptip.imgBlock, block, maptip);

			player->ToScreen();
			
			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();
			//Novice::ScreenPrintf(42, 120, "time: %f", timeElapsed);

			/////////////
			//描画処理　　↑↑↑↑↑↑↑↑
			/////////////

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
