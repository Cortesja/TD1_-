#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

const int kWindowHeight = 704;
const int kWindowWidth = 1280;

const int WORLD_WIDTH = kWindowWidth + (kWindowWidth / 2);
const int WORLD_HEIGHT = kWindowHeight + (kWindowHeight / 2);

const int bMapY = 22;
const int bMapX = 40;
const int BLOCK_SIZE = 32;

enum scene {
	gameTitle,
	gameColorSelect,
	gameStageSelect,
	gameStage1,
	gameStage2,
	gameStage3,
	gameOver
};

enum MapLegend {
	empty, //0 
	koteiBlock,//1
	kagi,//2
	tobira,//3
	togeUp,//4
	togeDown//5
};

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Vector2Int {
	int x;
	int y;
}Vector2Int;

typedef struct Size {
	float w;
	float h;
}Size;

typedef struct Matrix2x2 {
	float m[2][2];
}Matrix2x2;

typedef struct Matrix3x3 {
	float m[3][3];
}Matrix3x3;

typedef struct Position {
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;
}Position;

typedef struct PositionInt {
	Vector2Int leftTop;
	Vector2Int leftBottom;
	Vector2Int rightTop;
	Vector2Int rightBottom;
}PositionInt;

typedef struct Maptip final {
	int map1[22][40];
	int map2[22][40];
	int map3[22][40];
	int map4[22][40];
	Vector2 doorPos;
	Size size;
	int imgBlock[10];
	int imgKagi[4];
	int imgTobira[8];
	int imgToge[6];
	int timer;
	int imgHandler;
	bool kagiGet[2];
	bool stageClear;

	int effTimer_;
	int max_;
	int min_;
	int randx_;
	int randy_;

}Maptip;

typedef struct MaptipBlock final {
	Vector2 pos;
	int color;
	int R_;
	int G_;
	int B_;
	int A_;
}MaptipBlock;

Matrix3x3 MakeTranslateRotateMatrix(Vector2 translate, float theta);
Matrix3x3 MakeRotateMatrix(float theta);

float convertToSec(clock_t time);
float getElapsedTime(clock_t time);
bool chkObjHit(Vector2 playerPos, Size playerSize, Vector2 objPos, Size objSize);