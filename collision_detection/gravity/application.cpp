#include "application.h"

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
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				Body *ball = new Body(CircleShape(30), x, y, 1.0);
				bodies.push_back(ball);
			}
		default:
			break;
		}
	}
}

void Application::Update()
{
	Graphics::ClearScreen(0x808080);

	static int timePreviousFrame;
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
	if (deltaTime > 0.016)
	{
		deltaTime = 0.016;
	}

	timePreviousFrame = SDL_GetTicks();

	for (auto &body : bodies)
	{
		Vec2 weight = Vec2(0.0, body->mass * G * PIXELS_PER_METER);
		body->AddForce(weight);
	}

	for (auto &body : bodies)
	{
		body->IntegrateForces(deltaTime);
	}

	for (auto &body : bodies)
	{
		body->IntegrateVelocities(deltaTime);
	}
}

void Application::Render()
{
	for (auto body : bodies)
	{
		CircleShape *circleShape = (CircleShape *)body->shape;
		Graphics::DrawCircle(body->position.x, body->position.y, circleShape->radius, 0xFFFFFFFF);
	}

	Graphics::RenderFrame();
}

void Application::Destroy()
{
	Graphics::CloseWindow();
}