#pragma once
#include "myStructs.h"
#include "Color.h"
class MaptipBlock
{
public:
	Vector2 pos_;
	Color* color;
	int timer_;
public:
	MaptipBlock(int y, int x);
	~MaptipBlock();
	void Update(float timeElasped, bool &night);
	void Draw(int map[bMapY][bMapX], int imgBlock[10], int y, int x);
};