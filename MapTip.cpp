#include "MapTip.h"
#include "Novice.h"

void initializeMaptip(Maptip &maptip) {
	//1
	maptip.imgBlock[0] = Novice::LoadTexture("./resources/block.png");

	//6
	maptip.imgBlock[1] = Novice::LoadTexture("./resources/objects/bounce.png");

	//7
	maptip.imgBlock[2] = Novice::LoadTexture("./resources/kanban.png");

	//2
	maptip.imgKagi[0] = Novice::LoadTexture("./resources/objects/kagi.png");
	maptip.imgKagi[1] = Novice::LoadTexture("./resources/objects/kagiGet.png");

	//3
	maptip.imgTobira[0] = Novice::LoadTexture("./resources/objects/tobira1.png");
	maptip.imgTobira[1] = Novice::LoadTexture("./resources/objects/tobira2.png");
	maptip.imgTobira[2] = Novice::LoadTexture("./resources/objects/tobira3.png");
	maptip.imgTobira[3] = Novice::LoadTexture("./resources/objects/tobira4.png");
	maptip.imgTobira[4] = Novice::LoadTexture("./resources/objects/tobira5.png");
	maptip.imgTobira[5] = Novice::LoadTexture("./resources/objects/tobira6.png");
	maptip.imgTobira[6] = Novice::LoadTexture("./resources/objects/tobira7.png");
	maptip.imgTobira[7] = Novice::LoadTexture("./resources/objects/tobira8.png");

	//4
	maptip.imgToge[togeUp] = Novice::LoadTexture("./resources/objects/togeUp.png");
	//5
	maptip.imgToge[togeDown] = Novice::LoadTexture("./resources/objects/togeDown.png");

	maptip.timer = 0;
	maptip.imgHandler = 0;

	maptip.effTimer_ = 30;
	maptip.max_ = 41;
	maptip.min_ = 20;
	maptip.randx_= 0;
	maptip.randy_= 0;

	maptip.size = { 64.0f, 64.0f };
	maptip.stageClear = false;
}

void initializeMap(int map1[bMapY][bMapX], int map2[bMapY][bMapX], int map3[bMapY][bMapX], MaptipBlock block[bMapY][bMapX]) {

	int Map1[bMapY][bMapX] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,4,4,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1},
		{1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1},
		{1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,4,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,7,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,0,2,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,6,1}
	};

	int Map2[bMapY][bMapX] = {
		{1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,3,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,1},
		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,1},
		{1,1,0,0,5,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,5,5,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,5,5,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,6,0,4,4,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,1},
		{1,2,0,4,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,6,6,1,1,0,0,1,1,0,0,0,0,0,0,0,0,5,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,5,5,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,5,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,4,4,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,5,5,5,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,1}
	};

	int Map3[bMapY][bMapX] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	for (int y = 0; y < bMapY; y++)
	{
		for (int x = 0; x < bMapX; x++)
		{
			map1[y][x] = Map1[y][x];
			map2[y][x] = Map2[y][x];
			map3[y][x] = Map3[y][x];

			block[y][x].pos.x = (float)x * BLOCK_SIZE;
			block[y][x].pos.y = (float)y * BLOCK_SIZE;

			block[y][x].R_ = 255;
			block[y][x].G_ = 255;
			block[y][x].B_ = 255;
			block[y][x].A_ = 255;

			block[y][x].color = 0xFFFFFFFF;
		}
	}
}

void blockUpdate(float timeElapsed, bool &night, int &timer, MaptipBlock block[bMapY][bMapX], bool &reset) {
	if (timeElapsed >= 1200.0f) {
		night = true;
	}

	if (!night) {
		timer += 1;

		if (timer % 5 == 0) {
			for (int y = 0; y < bMapY; y++) {
				for (int x = 0; x < bMapX; x++) {
					block[y][x].R_ -= 1;
					block[y][x].G_ -= 1;
					block[y][x].B_ -= 1;
				}
			}
		}
	}
	else {
		for (int y = 0; y < bMapY; y++) {
			for (int x = 0; x < bMapX; x++) {
				block[y][x].R_ = 0;
				block[y][x].G_ = 0;
				block[y][x].B_ = 0;
			}
		}
	}

	if (reset) {
		for (int y = 0; y < bMapY; y++)
		{
			for (int x = 0; x < bMapX; x++)
			{
				block[y][x].R_ = 255;
				block[y][x].G_ = 255;
				block[y][x].B_ = 255;
				block[y][x].A_ = 255;

				block[y][x].color = 0xFFFFFFFF;
			}
		}

		reset = false;
	}

	//ToCode()
	for (int y = 0; y < bMapY; ++y) {
		for (int x = 0; x < bMapX; ++x) {
			block[y][x].color = (block[y][x].R_ << 24) + (block[y][x].G_ << 16) + (block[y][x].B_ << 8) + block[y][x].A_;
		}
	}
}

void MaptipScreenShake(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip &maptip, bool &isShake) {

		maptip.effTimer_--;

		if (maptip.effTimer_ <= 20 && maptip.effTimer_ > 10) {
			maptip.min_ = 15;
			maptip.max_ = 31;
		}
		if (maptip.effTimer_ <= 10 && maptip.effTimer_ > 0) {
			maptip.max_ = 11;
			maptip.min_ = 5;
		}

		maptip.randx_ = rand() % maptip.max_ - maptip.min_;
		maptip.randy_ = rand() % maptip.max_ - maptip.min_;

		if (maptip.effTimer_ <= 0) {
			isShake = false;
			maptip.max_ = 41;
			maptip.min_ = 20;
			maptip.effTimer_ = 30;
		}

		for (int y = 0; y < bMapY; y++) {
			for (int x = 0; x < bMapX; x++) {
				//////////////////////////

				if (map[y][x] == koteiBlock) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, imgBlock[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				if (map[y][x] == kagi) {
					if (!maptip.kagiGet[0]) {
						Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, maptip.imgKagi[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
					}
					else {
						Novice::DrawSprite(10, 10, maptip.imgKagi[1], 1.0f, 1.0f, 0.0f, WHITE);
					}
				}
				if (map[y][x] == tobira) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, maptip.imgTobira[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				if (map[y][x] == togeUp) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, maptip.imgToge[togeUp], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				if (map[y][x] == togeDown) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, maptip.imgToge[togeDown], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				if (map[y][x] == bounce) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, imgBlock[1], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				if (map[y][x] == kanban) {
					Novice::DrawSprite((int)block[y][x].pos.x + maptip.randx_, (int)block[y][x].pos.y + maptip.randy_, imgBlock[2], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}


				/////////////////////////
			}
		}
}
	

void DrawMaptip(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip &maptip) {
	for (int y = 0; y < bMapY; y++) {
		for (int x = 0; x < bMapX; x++) {
			//////////////////////////

			if (map[y][x] == koteiBlock) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, imgBlock[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == kagi) {
				if (!maptip.kagiGet[0]) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgKagi[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				else {
					Novice::DrawSprite(10, 10, maptip.imgKagi[1], 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
			if (map[y][x] == tobira) {
				if (maptip.stageClear) {
					maptip.timer++;
					if (maptip.timer % 15 == 0) {
						maptip.imgHandler += 1;
					}

					if (maptip.timer >= 120) {
						maptip.imgHandler = 7;
					}

					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgTobira[maptip.imgHandler], 1.0f, 1.0f, 0.0f, block[y][x].color);
				}
				else {
					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgTobira[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
					maptip.doorPos.x = block[y][x].pos.x;
					maptip.doorPos.y = block[y][x].pos.y;

				}
			}
			if (map[y][x] == togeUp) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeUp], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == togeDown) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeDown], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == bounce) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, imgBlock[1], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == kanban) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, imgBlock[2], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}


			/////////////////////////
		}
	}
}