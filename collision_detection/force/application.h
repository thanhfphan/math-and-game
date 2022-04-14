#pragma once

class Application {
	private:
		bool isRunning  = false;
	
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