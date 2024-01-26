#pragma once
#include "myStructs.h"

class Color
{
public:
	int R_ = 0;
	int G_ = 0;
	int B_ = 0;
	int A_ = 0;

	int maxR_ = 255;
	int maxG_ = 255;
	int maxB_ = 255;
	int maxA_ = 255;

	int colorHandler_ = 0;

public:

	void ToCode();
	void SetColor(int color);
};

