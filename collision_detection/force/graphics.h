#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

struct Graphics
{
	static int windowWidth;
	static int windowHeight;
	static SDL_Window *window;
	static SDL_Renderer *renderer;

	static int Height();
	static int Width();
	static bool OpenWindow();
	static void CloseWindow();
	static void ClearScreen(Uint32 color);
	static void RenderFrame();
	static void DrawLine(int x0, int y0, int x1, int y1, Uint32 color);
};
