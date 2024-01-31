#include <Novice.h>
#include "myStructs.h"
#include "Object.h"
#include "Player.h"
#include "Backround.h"
#include "MapTip.h"
#include "Light.h"
#include "Color.h"

const char kWindowTitle[] = "GC1C_ひとめちゃん";

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

	float timeElapsed = 0;

	bool night = false;
	int nightTimer = 0;
	int clearTimer = 0;
	bool reset = false;

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

			clearTimer = 0;
			timeElapsed = 0;
			maptip.kagiGet[0] = false;
			night = false;
			haikei1->night_ = false;

			player->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (player->easing->size_.h / 2)) };
			player->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (player->easing->size_.h / 2)) };
			player->easing->startFrame_ = 0;
			player->easing->endFrame_ = 180;

			haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (haikei1->easing->size_.h / 2)) };
			haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->easing->size_.h / 2)) };
			haikei1->easing->startFrame_ = 0;
			haikei1->easing->endFrame_ = 180;

			player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

			maptip.stageClear = false;
			maptip.imgHandler = 0;
			maptip.timer = 0;
			reset = true;
			player->isAlive_ = true;

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = gameStage1;
				timeElapsed = 0;
			}

			break; //gameTitle
#pragma region
		case gameStage1:
			timeElapsed++;

			player->MovePlayer(keys, preKeys, maptip.map1, clearTimer);
			player->Update(maptip.map1, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed, reset);
			haikei1->Draw();

			blockUpdate(timeElapsed, night, nightTimer, block, reset);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			if (player->isHit_) {
				MaptipScreenShake(maptip.map1, maptip.imgBlock, block, maptip, player->isHit_);
				night = true;
				haikei1->night_ = true;
			}
			else {
				DrawMaptip(maptip.map1, maptip.imgBlock, block, maptip);
			}

			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();
			//Novice::ScreenPrintf(42, 120, "time: %f", timeElapsed);

			if (player->isAlive_ == false) {
				player->easing->StartEasingElastic(player->easing->isMove_);
			}

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
						timeElapsed = 0;
						maptip.kagiGet[0] = false;
						night = false;
						haikei1->night_ = false;

						haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (haikei1->easing->size_.h / 2)) };
						haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->easing->size_.h / 2)) };
						haikei1->easing->startFrame_ = 0;
						haikei1->easing->endFrame_ = 180;

						player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

						maptip.stageClear = false;
						maptip.imgHandler = 0;
						maptip.timer = 0;
						reset = true;

						scene += 1;
					}
				}
			}

			//death

			if (player->isAlive_ == false && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				clearTimer = 0;
				maptip.kagiGet[0] = false;

				player->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (player->easing->size_.h / 2)) };
				player->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (player->easing->size_.h / 2)) };
				player->easing->startFrame_ = 0;
				player->easing->endFrame_ = 180;

				player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

				maptip.stageClear = false;
				maptip.imgHandler = 0;
				maptip.timer = 0;
				player->isAlive_ = true;
			}

			//reset

			if (player->isAlive_ == false && keys[DIK_R] && !preKeys[DIK_R]) {
				scene = gameTitle;
			}

			break; //gameStage1
#pragma endregion gameStage1
#pragma region
		case gameStage2:
			timeElapsed++;

			player->MovePlayer(keys, preKeys, maptip.map2, clearTimer);
			player->Update(maptip.map2, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed, reset);
			haikei1->Draw();

			////////////////////////////////////////

			Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
			theta += (float)(1.0f / 128.0f * (M_PI));

			spike->Multiply(rotateMatrix);
			spike->Update(timeElapsed, night, player->GetPosition(), player->isHit_, reset);
			if (player->isHit_) {
				player->isAlive_ = false;
				player->easing->isMove_ = true;
			}
			if (night) {
				spike->color->colorHandler_ = ChkVisible(playerLight->size_.w, player->GetPosition(), spike->position_);
			}
			spike->Draw();
			///////////////////////////////////////

			blockUpdate(timeElapsed, night, nightTimer, block, reset);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			if (player->isHit_) {
				MaptipScreenShake(maptip.map2, maptip.imgBlock, block, maptip, player->isHit_);
				night = true;;
				haikei1->night_ = true;
			}
			else {
				DrawMaptip(maptip.map2, maptip.imgBlock, block, maptip);
			}

			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();

			if (player->isAlive_ == false) {
				player->easing->StartEasingElastic(player->easing->isMove_);
			}
			
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
						timeElapsed = 0;
						maptip.kagiGet[0] = false;
						night = false;
						haikei1->night_ = false;

						haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(- 500.0f - (haikei1->easing->size_.h / 2))};
						haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->easing->size_.h / 2)) };
						haikei1->easing->startFrame_ = 0;
						haikei1->easing->endFrame_ = 180;

						player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

						maptip.stageClear = false;
						maptip.imgHandler = 0;
						maptip.timer = 0;
						reset = true;

						scene += 1;
					}
				}
			}

			//death

			if (player->isAlive_ == false && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				clearTimer = 0;
				maptip.kagiGet[0] = false;

				player->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (player->easing->size_.h / 2)) };
				player->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (player->easing->size_.h / 2)) };
				player->easing->startFrame_ = 0;
				player->easing->endFrame_ = 180;

				player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

				maptip.stageClear = false;
				maptip.imgHandler = 0;
				maptip.timer = 0;
				player->isAlive_ = true;
			}

			//reset

			if (player->isAlive_ == false && keys[DIK_R] && !preKeys[DIK_R]) {
				scene = gameTitle;
			}

			break;//gameStage2
#pragma endregion gameStage2
		case gameStage3:
			player->MovePlayer(keys, preKeys, maptip.map3, clearTimer);
			player->Update(maptip.map3, maptip);

			/////////////
			//描画処理　　↓↓↓↓↓↓↓↓
			/////////////

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);
			haikei1->Update(timeElapsed, reset);
			haikei1->Draw();

			blockUpdate(timeElapsed, night, nightTimer, block, reset);

			if (haikei1->night_) {
				for (int y = 0; y < bMapY; y++) {
					for (int x = 0; x < bMapX; x++) {
						block[y][x].color = ChkVisible(playerLight->size_.w, player->GetPosition(), block[y][x].pos);
					}
				}
			}

			if (player->isHit_) {
				MaptipScreenShake(maptip.map3, maptip.imgBlock, block, maptip, player->isHit_);
				night = true;
				haikei1->night_ = true;
			}
			else {
				DrawMaptip(maptip.map3, maptip.imgBlock, block, maptip);
			}

			Novice::SetBlendMode(BlendMode::kBlendModeAdd);
			if (haikei1->night_) {
				playerLight->Draw(player->GetPosition());
			}

			Novice::SetBlendMode(BlendMode::kBlendModeNone);
			player->Draw();
			//Novice::ScreenPrintf(42, 120, "time: %f", timeElapsed);

			if (player->isAlive_ == false) {
				player->easing->StartEasingElastic(player->easing->isMove_);
			}

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
						timeElapsed = 0;
						maptip.kagiGet[0] = false;
						night = false;
						haikei1->night_ = false;

						haikei1->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (haikei1->easing->size_.h / 2)) };
						haikei1->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (haikei1->easing->size_.h / 2)) };
						haikei1->easing->startFrame_ = 0;
						haikei1->easing->endFrame_ = 180;

						player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

						maptip.stageClear = false;
						maptip.imgHandler = 0;
						maptip.timer = 0;
						reset = true;

						scene += 1;
					}
				}
			}

			//death

			if (player->isAlive_ == false && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				clearTimer = 0;
				maptip.kagiGet[0] = false;

				player->easing->startPos_ = { float(kWindowWidth / 4), float(-500.0f - (player->easing->size_.h / 2)) };
				player->easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (player->easing->size_.h / 2)) };
				player->easing->startFrame_ = 0;
				player->easing->endFrame_ = 180;

				player->SetPosition({ 1000.0f, kWindowHeight - 64.0f });

				maptip.stageClear = false;
				maptip.imgHandler = 0;
				maptip.timer = 0;
				player->isAlive_ = true;
			}

			//reset

			if (player->isAlive_ == false && keys[DIK_R] && !preKeys[DIK_R]) {
				scene = gameTitle;
			}

			break; //gameStage3
		case gameClear:

			Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, BLACK, kFillModeSolid);
			Novice::DrawSprite(kWindowWidth / 4, kWindowHeight / 4, haikei1->img_[4], 1.0f, 1.0f, 0.0f, WHITE);

			if (keys[DIK_R] && !preKeys[DIK_R]) {
				scene = gameTitle;
			}
			break; //gameClear
		} //switch

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	player->~Player();
	haikei1->~Backround();
	titleScreen->~Backround();
	playerLight->~Light();
	spike->~Object();

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
