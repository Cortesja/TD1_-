#pragma once
#include "myStructs.h"

void initializeMaptip(Maptip &maptip);
void initializeMap(int map1[bMapY][bMapX], int map2[bMapY][bMapX], int map3[bMapY][bMapX]);
int ChkVisible(float radius, Vector2 playerPos, Vector2 objectPos);