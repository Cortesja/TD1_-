#include "Player.h"
#include "Novice.h"

//日本語

Player::Player() {
	this->pos_ = { 1000.0f, 500.0f };
	newPos_ = { 0 };
	this->radius_ = 25;
	size_ = { 32.0f, 32.0f };
	this->speed_ = 5;

	p_ = { 0 };


	accel_ = { 0.0f, 0.8f };
	vel_ = { 0.0f , 0.0f };

	main_ = new Camera();
}

Player::~Player() {
	delete main_;
}

void Player::MovePlayer(char keys[], char preKeys[], int maptipmap[bMapY][bMapX]) {
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
	if (keys[DIK_A]) {
		p_.leftTop.x = (int)((pos_.x - tempV.x) / BLOCK_SIZE);
		p_.leftTop.y = (int)(pos_.y / BLOCK_SIZE);

		p_.leftBottom.x = (int)((pos_.x - tempV.x) / BLOCK_SIZE);
		p_.leftBottom.y = (int)(((pos_.y + size_.h) - 1)/ BLOCK_SIZE);

		if (maptipmap[p_.leftTop.y][p_.leftTop.x] != koteiBlock && maptipmap[p_.leftBottom.y][p_.leftBottom.x] != koteiBlock) {
			vel_.x = -4.0f;
		}
		else {
			vel_.x = 0.0f;
		}
	} 
	else if (keys[DIK_D]) {
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
		vel_.x  = 0.0f;
	}

	//ジャンプの前に処理しないと
	vel_.y += accel_.y;

	//ジャンプ
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		vel_.y = -11.0f;
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

	//マップチップの当たり判定
	if (maptipmap[p_.leftBottom.y][p_.leftBottom.x] == koteiBlock || maptipmap[p_.rightBottom.y][p_.rightBottom.x] == koteiBlock) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.leftBottom.y * BLOCK_SIZE - size_.h);
	}
	
	if (maptipmap[p_.leftTop.y][p_.leftTop.x] == koteiBlock || maptipmap[p_.rightTop.y][p_.rightTop.x] == koteiBlock) {
		vel_.y = 0;
		pos_.y = floorf((float)p_.leftTop.y * BLOCK_SIZE + size_.h);
	}

	pos_.x += vel_.x;

}

void Player::Update() {
	//縦横制限
	if (pos_.y >= kWindowHeight - size_.h) {
		pos_.y = kWindowHeight - size_.h;
	}

	//横制限
	if (pos_.x <= 0 - size_.w) {
		pos_.x = kWindowWidth - 1;
	}
	if (pos_.x >= kWindowWidth) {
		pos_.x = 0 - size_.w;
	}
}

void Player::ToScreen() {
	//pos_ = main_->ToScreenV2(pos_);
}

void Player::Draw() {
	Novice::DrawBox((int)pos_.x, (int)pos_.y, (int)size_.w, (int)size_.h, 0.0f,BLACK, kFillModeSolid);
}