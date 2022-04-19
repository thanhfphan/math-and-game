#include "graphics.h"
#include <iostream>

int Graphics::windowWidth = 0;
int Graphics::windowHeight = 0;
SDL_Window *Graphics::window = NULL;
SDL_Renderer *Graphics::renderer = NULL;

int Graphics::Height()
{
	return windowHeight;
}

int Graphics::Width()
{
	return windowWidth;
}

bool Graphics::OpenWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Initializing SDL failed " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow("Sanbox - Physics Engine", 0, 0, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		std::cerr << "Create SDL Window failed: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		std::cerr << "Create SDL Renderer failed: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Graphics::CloseWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::ClearScreen(Uint32 color)
{
	Uint8 r = (color >> 16) & 0xFF;
	Uint8 g = (color >> 8) & 0xFF;
	Uint8 b = color & 0xFF;
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderClear(renderer);
}

void Graphics::RenderFrame()
{
	SDL_RenderPresent(renderer);
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Uint32 color)
{
	lineColor(renderer, x0, y0, x1, y1, color);
}

void Graphics::DrawCircle(int x, int y, int radius, Uint32 color)
{
	filledCircleColor(renderer, x, y, radius, color);
}