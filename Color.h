#pragma once
#include "myStructs.h"

class Color
{
public:
	int R_;
	int G_;
	int B_;
	int A_;

	int maxR_ = 255;
	int maxG_ = 255;
	int maxB_ = 255;
	int maxA_ = 255;

	int colorHandler_;

public:

	void ToCode();
	void SetColor(int color);
};

