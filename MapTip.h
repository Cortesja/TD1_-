#pragma once
#include "myStructs.h"

void initializeMaptip(Maptip &maptip);
void initializeMap(int map1[bMapY][bMapX], int map2[bMapY][bMapX], int map3[bMapY][bMapX], MaptipBlock maptipPos[bMapY][bMapX]);
void blockUpdate(float timeElasped, bool &night, int &timer, MaptipBlock block[bMapY][bMapX], bool &reset);
void DrawMaptip(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip &maptip);

void MaptipScreenShake(int map[bMapY][bMapX], int imgBlock[10], MaptipBlock block[bMapY][bMapX], Maptip &maptip, bool &isShake);