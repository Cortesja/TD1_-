#pragma once
#include "myStructs.h"

void initializeMaptip(Maptip &maptip);
void initializeMap(int map1[bMapY][bMapX], int map2[bMapY][bMapX], int map3[bMapY][bMapX], MaptipBlock maptipPos[bMapY][bMapX]);
void blockUpdate(float timeElasped, bool &night, int &timer, MaptipBlock block[bMapY][bMapX]);
int ChkVisible(float radius, Vector2 playerPos, Vector2 objectPos);
void DrawMaptip(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX]);