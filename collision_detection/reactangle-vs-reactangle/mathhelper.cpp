#include <SDL2/SDL.h>
#include "mathhelper.h"

int Min(int val1, int val2)
{
	if (val1 > val2)
	{
		return val2;
	}
	return val1;
}
int Max(int val1, int val2)
{
	if (val1 > val2)
	{
		return val1;
	}
	return val2;
}
bool IsInRange(int value, int min, int max)
{
	return value >= min && value <= max;
}

bool IsPointInRect(int x, int y, SDL_Rect rect)
{
	return IsInRange(x, rect.x, rect.x + rect.w) && IsInRange(y, rect.y, rect.y + rect.h);
}

bool IsRangeIntersect(int min0, int max0, int min1, int max1){
	return Max(min0, max0) >= Min(min1, max1) && Min(min0, max0) <= Max(min1, max1);
}

bool IsRectIntersect(SDL_Rect rect1, SDL_Rect rect2)
{
	return IsRangeIntersect(rect1.x, rect1.x + rect1.w, rect2.x, rect2.x + rect2.w) && IsRangeIntersect(rect1.y, rect1.y + rect1.h, rect2.y, rect2.y + rect2.h);
}