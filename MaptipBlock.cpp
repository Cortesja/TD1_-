#include "MaptipBlock.h"
#include "Novice.h"

MaptipBlock::MaptipBlock(int y, int x) {
	pos_.y = (float)y * BLOCK_SIZE;
	pos_.x = (float)x * BLOCK_SIZE;

	color = new Color;

	color->R_ = 255;
	color->G_ = 255;
	color->B_ = 255;

	color->colorHandler_ = 0xFFFFFFFF;

	timer_ = 0;
}

MaptipBlock::~MaptipBlock() {

}

void MaptipBlock::Update(float timeElasped, bool &night) {
	if (timeElasped >= 43.0f) {
		night = true;
	}

	if (!night) {
		timer_ += 1;

		if (timer_ % 10 == 0) {
			color->R_ -= 1;
			color->G_ -= 1;
			color->B_ -= 1;
		}
	}
	else {
		color->R_ = 0;
		color->G_ = 0;
		color->B_ = 0;
	}

	color->ToCode();
}

void MaptipBlock::Draw(int map[bMapY][bMapX], int imgBlock[10], int y, int x) {
	if (map[y][x] == koteiBlock) {
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, imgBlock[0], 1.0f, 1.0f, 0.0f, color->colorHandler_);
	}
}