#pragma once

#include "graphics.h"
#include "body.h"
#include <vector>

class Application {
	private:
		bool isRunning  = false;

		float G = 9.8;
		const int MILLISECS_PER_FRAME = 50;
		const int PIXELS_PER_METER = 900;
		std::vector<Body*> bodies;
	
	public:
		Application() = default;
		~Application() = default;
		bool IsRunning();
		void SetUp();
		void Input();
		void Update();
		void Render();
		void Destroy();
};