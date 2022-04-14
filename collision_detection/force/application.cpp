#include "application.h"
#include "graphics.h"

bool Application::IsRunning()
{
	return isRunning;
}

void Application::SetUp()
{
	isRunning = Graphics::OpenWindow();
}

void Application::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			break;

		default:
			break;
		}
	}
}

void Application::Update()
{
	Graphics::ClearScreen(0x808080);
}

void Application::Render()
{
	Graphics::DrawLine(100, 100, 600, 600, 0xFFFFFFFF);
	Graphics::RenderFrame();
}

void Application::Destroy()
{
	Graphics::CloseWindow();
}