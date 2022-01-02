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
SDL_Rect rect1;
SDL_Rect rect2;

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
	if (screenSurface == NULL) {
		std::cout << "Create window surface failed , err=" << SDL_GetError() << std::endl;
		return 1;
	}
	TRY(SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xDD, 0xDD, 0xDD)));
	// texture
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screenSurface);
	TRY(SDL_RenderCopy(renderer, texture, NULL, NULL));

	rect1.x = 100;
	rect1.y = 210;
	rect1.h = 300;
	rect1.w = 300;

	rect2.x = 600;
	rect2.y = 600;
	rect2.h = 100;
	rect2.w = 150;

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
					if (movObj == "rect1")
					{
						rect1.x = event.motion.x;
						rect1.y = event.motion.y;
					}
					if (movObj == "rect2")
					{
						rect2.x = event.motion.x;
						rect2.y = event.motion.y;
					}
				}
			case SDL_MOUSEBUTTONDOWN:

				if (IsPointInRect(event.button.x, event.button.y, rect1) && SDL_BUTTON_LEFT == event.button.button)
				{
					movObj = "rect1";
				}
				if (IsPointInRect(event.button.x, event.button.y, rect2) && SDL_BUTTON_LEFT == event.button.button)
				{
					movObj = "rect2";
				}
				break;
			case SDL_MOUSEBUTTONUP:
				movObj = "";
				break;
			}

			if (IsRectIntersect(rect1, rect2))
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			}
		}

		SDL_RenderFillRect(renderer, &rect1);
		SDL_RenderFillRect(renderer, &rect2);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
