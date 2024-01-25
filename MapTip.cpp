#include "MapTip.h"
#include "Novice.h"

void initializeMaptip(Maptip &maptip) {
	maptip.imgBlock[0] = Novice::LoadTexture("./resources/block.png");
	maptip.imgKagi[0] = Novice::LoadTexture("./resources/objects/kagi.png");
	maptip.imgKagi[1] = Novice::LoadTexture("./resources/objects/kagiGet.png");

	maptip.imgTobira[0] = Novice::LoadTexture("./resources/objects/tobira1.png");
	maptip.imgTobira[1] = Novice::LoadTexture("./resources/objects/tobira2.png");
	maptip.imgTobira[2] = Novice::LoadTexture("./resources/objects/tobira3.png");
	maptip.imgTobira[3] = Novice::LoadTexture("./resources/objects/tobira4.png");
	maptip.imgTobira[4] = Novice::LoadTexture("./resources/objects/tobira5.png");
	maptip.imgTobira[5] = Novice::LoadTexture("./resources/objects/tobira6.png");
	maptip.imgTobira[6] = Novice::LoadTexture("./resources/objects/tobira7.png");
	maptip.imgTobira[7] = Novice::LoadTexture("./resources/objects/tobira8.png");

	maptip.imgToge[togeUp] = Novice::LoadTexture("./resources/objects/togeUp.png");
	maptip.imgToge[togeDown] = Novice::LoadTexture("./resources/objects/togeDown.png");

	maptip.timer = 0;

	maptip.effTimer_ = 90;
	maptip.max_ = 51;
	maptip.min_ = 25;
	maptip.randx_= 0;
	maptip.randy_= 0;
	maptip.isShake_ = false;
}

void initializeMap(int map1[bMapY][bMapX], int map2[bMapY][bMapX], int map3[bMapY][bMapX], MaptipBlock block[bMapY][bMapX]) {

	int Map1[bMapY][bMapX] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,4,4,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,0,2,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int Map2[bMapY][bMapX] = {
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

int ChkVisible(float radius, Vector2 playerPos, Vector2 objectPos) {
	float distance = sqrtf(powf(objectPos.x - playerPos.x, 2) + powf(objectPos.y - playerPos.y, 2));

	//if (radius * 0.75 <= distance) {
	//	return 0x00000000;
	//}
	//else if (radius * 0.6 <= distance) {
	//	return 0x33333333;
	//}
	//else if (radius * 0.5 <= distance) {
	//	return 0x44444444;
	//} 
	//else if (radius * 0.25 <= distance) {
	//	return 0xBBBBBBBB;
	//}
	//else {
	//	return 0xFFFFFFFF;
	//}

	if (radius * 0.55 <= distance) {
		return 0x000000FF;
	}
	else if (radius * 0.5 <= distance) {
		return 0x444444FF;
	}
	else {
		return 0x888888FF;
	}
}

void blockUpdate(float timeElapsed, bool &night, int &timer, MaptipBlock block[bMapY][bMapX]) {
	if (timeElapsed >= 40.0f) {
		night = true;
	}

	if (!night) {
		timer += 1;
	}

	if (!night) {
		if (timer % 10 == 0) {
			for (int y = 0; y < bMapY; y++) {
				for (int x = 0; x < bMapX; x++) {
					if (timer % 10 == 0) {
						block[y][x].R_ -= 1;
						block[y][x].G_ -= 1;
						block[y][x].B_ -= 1;
					}
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
	//ToCode()
	for (int y = 0; y < bMapY; ++y) {
		for (int x = 0; x < bMapX; ++x) {
			block[y][x].color = (block[y][x].R_ << 24) + (block[y][x].G_ << 16) + (block[y][x].B_ << 8) + block[y][x].A_;
		}
	}
}

//void MaptipScreenShake(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip maptip, bool isHit) {
//
//	if (isHit) {
//		effTimer_--;
//
//		if (effTimer_ <= 60 && effTimer_ > 30) {
//			min_ = 15;
//			max_ = 31;
//		}
//		if (effTimer_ <= 30 && effTimer_ > 0) {
//			max_ = 11;
//			min_ = 5;
//		}
//
//		randx_ = rand() % max_ - min_;
//		randy_ = rand() % max_ - min_;
//
//		if (effTimer_ <= 0) {
//			isShake_ = false;
//			max_ = 51;
//			min_ = 25;
//			effTimer_ = 90;
//		}
//
//		for (int y = 0; y < bMapY; y++) {
//			for (int x = 0; x < bMapX; x++) {
//				//////////////////////////
//
//				if (map[y][x] == koteiBlock) {
//					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, imgBlock[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
//				}
//				if (map[y][x] == kagi) {
//					if (!maptip.kagiGet[0]) {
//						Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgKagi[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
//					}
//					else {
//						Novice::DrawSprite(10, 10, maptip.imgKagi[1], 1.0f, 1.0f, 0.0f, WHITE);
//					}
//				}
//				if (map[y][x] == tobira) {
//					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgTobira[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
//				}
//				if (map[y][x] == togeUp) {
//					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeUp], 1.0f, 1.0f, 0.0f, block[y][x].color);
//				}
//				if (map[y][x] == togeDown) {
//					Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeDown], 1.0f, 1.0f, 0.0f, block[y][x].color);
//				}
//
//
//				/////////////////////////
//			}
//		}
//	}
//}

void DrawMaptip(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip maptip, bool isHit) {
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
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgTobira[0], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == togeUp) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeUp], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}
			if (map[y][x] == togeDown) {
				Novice::DrawSprite((int)block[y][x].pos.x, (int)block[y][x].pos.y, maptip.imgToge[togeDown], 1.0f, 1.0f, 0.0f, block[y][x].color);
			}


			/////////////////////////
		}
	}
}