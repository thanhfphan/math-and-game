#pragma once
#include <SDL2/SDL.h>

struct Point
{
	int x, y;
};

struct Line
{
	Point point1, point2;
};

int Min(int, int);
int Max(int, int);
bool IsInRange(int value, int min, int max);
bool IsPointInRect(int x, int y, SDL_Rect rect);
bool IsRangeIntersect(int min0, int max0, int min1, int max1);
bool IsRectIntersect(SDL_Rect rect1, SDL_Rect rect2);
double Distance2Point(Point, Point);
double Distance2Point(int x0, int y0, int x1, int y1);