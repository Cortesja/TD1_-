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
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int scene = gameTitle;

	Player* player = new Player();
	Light* playerLight = new Light();
	Backround* haikei1 = new Backround();
	Backround* titleScreen = new Backround();

	Object* spike = new Object();

	Maptip maptip = { 0 };
	MaptipBlock block[bMapY][bMapX];

	initializeMaptip(maptip);
	initializeMap(maptip.map1, maptip.map2, maptip.map3, block);

	clock_t startingTime = clock();
	float timeElapsed = 0;

	bool night = false;
	//bool isShake = false;
	int nightTimer = 0;
	int clearTimer = 0;

	float theta = 0.0f;

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
			Novice::SetBlendMode(BlendMode::kBlendModeNormal);

			titleScreen->DrawTitleScreen();

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = gameStage1;
				timeElapsed = 0;
				startingTime = clock();
			}

			break; //gameTitle
		case gameColorSelect:
			break; //gameColorSelect
#pragma region
		case gameStage1:
			timeElapsed = getElapsedTime(startingTime);

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				night = true;
				haikei1->night_ = true;
			}

			player->MovePlayer(keys, preKeys, maptip.map1);
			player->Update(maptip.map1, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed);
			haikei1->Draw();

			blockUpdate(timeElapsed, night, nightTimer, block);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			if (player->isHit_) {
				MaptipScreenShake(maptip.map1, maptip.imgBlock, block, maptip, player->isHit_);
			}
			else {
				DrawMaptip(maptip.map1, maptip.imgBlock, block, maptip);
			}

			player->ToScreen();
			
			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();
			Novice::ScreenPrintf(42, 120, "time: %f", timeElapsed);

			/////////////
			//描画処理　　↑↑↑↑↑↑↑↑
			/////////////

			//stageClear

			if (maptip.stageClear) {
				clearTimer++;

				if (clearTimer == 120) {
					haikei1->easing->isMove_ = true;
				}

				if (clearTimer > 120) {
					haikei1->easing->StartEasing(haikei1->easing->isMove_);

					if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
						clearTimer = 0;
						startingTime = clock();
						timeElapsed = 0;
						maptip.kagiGet[0] = false;
						night = false;
						haikei1->night_ = false;

						haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (haikei1->size_.h / 2)) };
						haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->size_.h / 2)) };
						haikei1->easing->startFrame_ = 0;
						haikei1->easing->endFrame_ = 180;

						player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

						maptip.stageClear = false;
						maptip.imgHandler = 0;
						maptip.timer = 0;

						scene += 1;
					}
				}
			}

			break; //gameStage1
#pragma endregion gameStage1
#pragma region
		case gameStage2:
			timeElapsed = getElapsedTime(startingTime);

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				night = true;
				haikei1->night_ = true;
			}

			player->MovePlayer(keys, preKeys, maptip.map2);
			player->Update(maptip.map2, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////

			//Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed);
			haikei1->Draw();

			blockUpdate(timeElapsed, night, nightTimer, block);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			////////////////////////////////////////

			Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
			theta += (float)(1.0f / 128.0f * (M_PI));

			spike->Multiply(rotateMatrix);
			spike->Update(timeElapsed, night, player->GetPosition(), player->isHit_);
			if (night) {
				spike->color->colorHandler_ = ChkVisible(playerLight->size_.w, player->GetPosition(), spike->position_);
			}
			spike->Draw();
			///////////////////////////////////////

			if (player->isHit_) {
				MaptipScreenShake(maptip.map2, maptip.imgBlock, block, maptip, player->isHit_);
			}
			else {
				DrawMaptip(maptip.map2, maptip.imgBlock, block, maptip);
			}

			player->ToScreen();

			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();
			//Novice::DrawEllipse((int)player->GetPosition().x, (int)player->GetPosition().y, 5, 5, 0.0f, RED, kFillModeSolid);
			//Novice::ScreenPrintf(42, 120, "time: %f", timeElapsed);
			
			/////////////
			//描画処理　　↑↑↑↑↑↑↑↑
			/////////////

			//stageClear

			if (maptip.stageClear) {
				clearTimer++;

				if (clearTimer == 120) {
					haikei1->easing->isMove_ = true;
				}

				if (clearTimer > 120) {
					haikei1->easing->StartEasing(haikei1->easing->isMove_);

					if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
						clearTimer = 0;
						startingTime = clock();
						timeElapsed = 0;
						maptip.kagiGet[0] = false;
						night = false;
						haikei1->night_ = false;

						haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(- 500.0f - (haikei1->size_.h / 2))};
						haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->size_.h / 2)) };
						haikei1->easing->startFrame_ = 0;
						haikei1->easing->endFrame_ = 180;

						player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

						maptip.stageClear = false;
						maptip.imgHandler = 0;
						maptip.timer = 0;

						scene += 1;
					}
				}
			}

			break;//gameStage2
#pragma endregion gameStage2
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
