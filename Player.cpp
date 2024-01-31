#include "Player.h"
#include "Novice.h"

//日本語

Player::Player() {
	this->pos_ = { 1000.0f, kWindowHeight - 64.0f };
	newPos_ = { 0 };
	this->radius_ = 25;
	size_ = { 32.0f, 32.0f };
	this->speed_ = 5;

	p_ = { 0 };


	accel_ = { 0.0f, 0.8f };
	vel_ = { 4.0f , 0.0f };

	img_[0] = Novice::LoadTexture("./resources/player/player.png"), imgDeath[0] = Novice::LoadTexture("./resources/player/playerDeath.png"),
		imgDeath[1] = Novice::LoadTexture("./resources/player/playerDeath1.png");
	color_ = 0xFFFFFFFF;

	isHit_ = false;
	isAlive_ = true;
	jumpCount_ = 0;

	easing = new Easing;
	easing->size_ = { 640.0f, 352.0f };

	easing->startPos_ = { float(kWindowWidth / 4), -500.0f - (easing->size_.h / 2) };
	easing->endPos_ = { float(kWindowWidth / 4), float(kWindowHeight / 2 - (easing->size_.h / 2)) };

	easing->startFrame_ = 0;
	easing->endFrame_ = 180;

	easing->img_ = Novice::LoadTexture("./resources/gameOver.png");
}

Player::~Player() {
	easing->~Easing();
}

void Player::MovePlayer(char keys[], char preKeys[], int maptipmap[bMapY][bMapX], int clearTimer) {
	Vector2 tempV = { 4.0f, 0.0f };

	//マップチップ座標を取得　pos_ / ブロックサイズ
	
	p_.leftTop.x = (int)(pos_.x / BLOCK_SIZE);
	p_.leftTop.y = (int)(pos_.y / BLOCK_SIZE);

	p_.leftBottom.x = (int)(pos_.x / BLOCK_SIZE);
	p_.leftBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

	p_.rightTop.x = (int)(((pos_.x + size_.w) - 1) / BLOCK_SIZE);
	p_.rightTop.y = (int)(pos_.y / BLOCK_SIZE);

	p_.rightBottom.x = (int)(((pos_.x + size_.w) - 1) / BLOCK_SIZE);
	p_.rightBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

	//////////////////////

	//左右移動
	 
	if (keys[DIK_A] && isAlive_ == true && clearTimer < 1) {
		p_.leftTop.x = (int)((pos_.x - tempV.x) / BLOCK_SIZE);
		p_.leftTop.y = (int)(pos_.y / BLOCK_SIZE);

		p_.leftBottom.x = (int)((pos_.x - tempV.x) / BLOCK_SIZE);
		p_.leftBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

		if (maptipmap[p_.leftTop.y][p_.leftTop.x] != koteiBlock && maptipmap[p_.leftBottom.y][p_.leftBottom.x] != koteiBlock) {
			vel_.x = -4.0f;
		}
		else {
			vel_.x = 0.0f;
		}
	}
	else if (keys[DIK_D] && isAlive_ == true && clearTimer < 1) {
		p_.rightTop.x = (int)((((pos_.x + size_.w) + tempV.x) - 1) / BLOCK_SIZE);
		p_.rightTop.y = (int)(pos_.y / BLOCK_SIZE);

		p_.rightBottom.x = (int)((((pos_.x + size_.w) +  tempV.x) - 1) / BLOCK_SIZE);
		p_.rightBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

		if (maptipmap[p_.rightTop.y][p_.rightTop.x] != koteiBlock && maptipmap[p_.rightBottom.y][p_.rightBottom.x] != koteiBlock) {
			vel_.x = 4.0f;
		}
		else {
			vel_.x = 0.0f;
		}
	}
	else {
		vel_.x = 0.0f;
	}

	//ジャンプの前に処理しないと
	vel_.y += accel_.y;

	//ジャンプ
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && jumpCount_ == 0 && isAlive_ == true && clearTimer < 1) {
		vel_.y = -11.0f;
		jumpCount_ += 1;
	}

	pos_.y += vel_.y;

	//二回目のマップ座標を取得
	p_.leftTop.x = (int)(pos_.x / BLOCK_SIZE);
	p_.leftTop.y = (int)(pos_.y / BLOCK_SIZE);

	p_.leftBottom.x = (int)(pos_.x / BLOCK_SIZE);
	p_.leftBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

	p_.rightTop.x = (int)(((pos_.x + size_.w) - 1) / BLOCK_SIZE);
	p_.rightTop.y = (int)(pos_.y / BLOCK_SIZE);

	p_.rightBottom.x = (int)(((pos_.x + size_.w) - 1) / BLOCK_SIZE);
	p_.rightBottom.y = (int)(((pos_.y + size_.h) - 1) / BLOCK_SIZE);

	pos_.x += vel_.x;
}

void Player::Update(int maptipmap[bMapY][bMapX], Maptip &maptip) {

	//縦横制限
	if (pos_.y >= kWindowHeight - size_.h) {
		pos_.y = 0 - size_.h / 2;
	}
	if (pos_.y <= 0 - size_.h) {
		pos_.y = kWindowHeight - size_.h;
	}

	//横制限
	if (pos_.x <= 0 - size_.w * 0.8f) {
		pos_.x = kWindowWidth - size_.w * 0.8f;
	}
	if (pos_.x >= kWindowWidth) {
		pos_.x = 0;
	}

	//マップチップの当たり判定

	//-------------- koteiBlock ---------------
	if (maptipmap[p_.leftBottom.y][p_.leftBottom.x] == koteiBlock) {
		vel_.y = 0;
		jumpCount_ = 0;
		pos_.y = floorf((float)p_.leftBottom.y * BLOCK_SIZE - size_.h);
	}

	if (maptipmap[p_.leftTop.y][p_.leftTop.x] == koteiBlock) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.leftTop.y * BLOCK_SIZE + size_.h);
	}

	if (maptipmap[p_.rightBottom.y][p_.rightBottom.x] == koteiBlock) {
		vel_.y = 0;
		jumpCount_ = 0;
		pos_.y = floorf((float)p_.rightBottom.y * BLOCK_SIZE - size_.h);
	}

	if (maptipmap[p_.rightTop.y][p_.rightTop.x] == koteiBlock) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.rightTop.y * BLOCK_SIZE + size_.h);
	}

	//-----------------------------------------

	//--------------- kagi -------------------
	if (maptipmap[p_.leftTop.y][p_.leftTop.x] == kagi || maptipmap[p_.leftBottom.y][p_.leftBottom.x] == kagi) {
		maptip.kagiGet[0] = true;
	}
	//----------------------------------------

	//--------------- toge ------------------
	if (maptipmap[p_.leftBottom.y][p_.leftBottom.x] == togeUp || maptipmap[p_.rightBottom.y][p_.rightBottom.x] == togeUp) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.leftBottom.y * BLOCK_SIZE - size_.h);

		if (isAlive_) {
			isHit_ = true;
			isAlive_ = false;
			easing->isMove_ = true;
		}
	}
	if (maptipmap[p_.leftTop.y][p_.leftTop.x] == togeDown || maptipmap[p_.rightTop.y][p_.rightTop.x] == togeDown) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.leftTop.y * BLOCK_SIZE + size_.h);

		if (isAlive_) {
			isHit_ = true;
			isAlive_ = false;
			easing->isMove_ = true;
		}
	}
	//---------------------------------------

	//-------------- tobira ----------------
	bool chkCollision;
	chkCollision = chkObjHit(pos_, size_, maptip.doorPos, maptip.size);
	if (chkCollision && maptip.kagiGet[0]) {

		maptip.stageClear = true;
	}
	//--------------------------------------

	//--------------- bouce ----------------
	if (maptipmap[p_.leftBottom.y][p_.leftBottom.x] == bounce || maptipmap[p_.rightBottom.y][p_.rightBottom.x] == bounce) {
		vel_.y = -20.0f;
	}
	if (maptipmap[p_.leftTop.y][p_.leftTop.x] == bounce || maptipmap[p_.rightTop.y][p_.rightTop.x] == bounce) {
		vel_.y = -20.0f;
	}
	//---------------------------------------
}

void Player::Draw() {
	if (isAlive_) {
	Novice::DrawSprite((int)pos_.x, (int)pos_.y, img_[0], 1.0f, 1.0f, 0.0f, color_);
	}
	else {
		Novice::DrawSprite((int)pos_.x, (int)pos_.y, imgDeath[0], 1.0f, 1.0f, 0.0f, color_);
	}

	//Novice::ScreenPrintf(42, 42, "p_.leftTop[%d][%d] ", p_.leftTop.y, p_.leftTop.x);
	//Novice::ScreenPrintf(42, 62, "p_.leftBottom[%d][%d] ", p_.leftBottom.y, p_.leftBottom.x);
	//Novice::ScreenPrintf(242, 42, "p_.rightTop[%d][%d] ", p_.rightTop.y, p_.rightTop.x);
	//Novice::ScreenPrintf(242, 62, "p_.rightBottom[%d][%d] ", p_.rightBottom.y, p_.rightBottom.x);

	//Novice::ScreenPrintf(42, 80, "pos_.x = %f", pos_.x);
	//Novice::ScreenPrintf(42, 100, "pos_.y = %f", pos_.y);
}