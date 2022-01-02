#pragma once
#include <SDL2/SDL.h>

int Min(int, int);
int Max(int, int);
bool IsInRange(int value, int min, int max);
bool IsPointInRect(int x, int y, SDL_Rect rect);
bool IsRangeIntersect(int min0, int max0, int min1, int max1);
bool IsRectIntersect(SDL_Rect rect1, SDL_Rect rect2);