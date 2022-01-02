#include <SDL2/SDL.h>
#include <iostream>
#include "mathhelper.h"
#include "string.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;

bool isRunning = true;
SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Surface *screenSurface;

void TRY(int flag)
{
	if (flag != 0)
	{
		std::cout << "Got err=" << SDL_GetError() << std::endl;
		exit(1);
	}
}

int main(int argc, char *args[])
{
	TRY(SDL_Init(SDL_INIT_VIDEO));

	window = SDL_CreateWindow("Collision Detection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Create window failed, err=" << SDL_GetError() << std::endl;
		return 1;
	}
	//renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL)
	{
		std::cout << "Create renderer failed , err=" << SDL_GetError() << std::endl;
		return 1;
	}
	//surface
	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == NULL)
	{
		std::cout << "Create window surface failed , err=" << SDL_GetError() << std::endl;
		return 1;
	}
	TRY(SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xDD, 0xDD, 0xDD)));
	// texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screenSurface);
	TRY(SDL_RenderCopy(renderer, texture, NULL, NULL));

	Point point11 = Point{130, 500};
	Point point12 = Point{1000, 500};
	Point point21 = Point{600, 700};
	Point point22 = Point{900, 150};
	SDL_Rect intersecPoint;
	int offset = 10;
	intersecPoint.h = offset * 2;
	intersecPoint.w = offset * 2;
	std::string movObj;
	while (isRunning)
	{
		// limiting the FPS
		auto time = SDL_GetTicks();
		if ((SDL_GetTicks() - time) < 10)
		{
			SDL_Delay(10);
		}

		TRY(SDL_RenderClear(renderer));
		TRY(SDL_RenderCopy(renderer, texture, NULL, NULL));

		TRY(SDL_RenderDrawLine(renderer, point11.x, point11.y, point12.x, point12.y));
		TRY(SDL_RenderDrawLine(renderer, point21.x, point21.y, point22.x, point22.y));

		// EventS
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				if (movObj != "")
				{
					if (movObj == "point11")
					{
						point11.x = event.motion.x;
						point11.y = event.motion.y;
					}
					else if (movObj == "point12")
					{
						point12.x = event.motion.x;
						point12.y = event.motion.y;
					}
					else if (movObj == "point21")
					{
						point21.x = event.motion.x;
						point21.y = event.motion.y;
					}
					else if (movObj == "point22")
					{
						point22.x = event.motion.x;
						point22.y = event.motion.y;
					}
				}
			case SDL_MOUSEBUTTONDOWN:
				if (SDL_BUTTON_LEFT == event.button.button)
				{
					Point mousePoint = {event.button.x, event.button.y};
					if (Distance2Point(point11, mousePoint) < 20)
					{
						movObj = "point11";
					}
					else if (Distance2Point(point12, mousePoint) < 20)
					{
						movObj = "point12";
					}
					else if (Distance2Point(point21, mousePoint) < 20)
					{
						movObj = "point21";
					}
					else if (Distance2Point(point22, mousePoint) < 20)
					{
						movObj = "point22";
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
				movObj = "";
				break;
			}
		}

		// Render point where 2 segment intersect
		int a1 = point12.y - point11.y;
		int b1 = point11.x - point12.x;
		int c1 = a1 * point11.x + b1 * point11.y;

		int a2 = point22.y - point21.y;
		int b2 = point21.x - point22.x;
		int c2 = a2 * point21.x + b2 * point21.y;

		int denominator = a1 * b2 - a2 * b1;
		if (denominator != 0)
			{
				int rectX = (c1 * b2 - c2 * b1) / denominator;
				int rectY = (c2 * a1 - c1 * a2) / denominator;
				float rx0 = (float)(rectX - Min(point12.x, point11.x)) / (Max(point12.x, point11.x) - Min(point12.x, point11.x));
				float ry0 = (float)(rectY - Min(point11.y, point12.y)) / (Max(point12.y, point11.y) - Min(point12.y, point11.y));
				float rx1 = (float)(rectX - Min(point21.x, point22.x)) / (Max(point22.x , point21.x) - Min(point22.x, point21.x));
				float ry1 = (float)(rectY - Min(point21.y, point22.y)) / (Max(point22.y , point21.y) - Min(point22.y, point21.y));
				if (((0 <= rx0 && rx0 <= 1) || (0 <= ry0 && ry0 <= 1)) && ((0 <= rx1 && rx1 <= 1) || (0 <= ry1 && ry1 <= 1)))
				{
					intersecPoint.x = rectX - offset;
					intersecPoint.y = rectY - offset;
					TRY(SDL_RenderFillRect(renderer, &intersecPoint));
				}
			}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
