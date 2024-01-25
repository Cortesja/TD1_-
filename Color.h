#pragma once
#include "myStructs.h"

class Color
{
public:
	int R_ = 255;
	int G_ = 255;
	int B_ = 255;
	int A_ = 255;

	int maxR_ = 255;
	int maxG_ = 255;
	int maxB_ = 255;
	int maxA_ = 255;

	int colorHandler_;

public:

	void ToCode();
	void SetColor(int color);
};

