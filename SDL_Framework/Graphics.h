#pragma once
#include <SDL.h>
#include <iostream>

namespace SDLFramework
{
	class Graphics{
	public:
		static const int SCREEN_WIDTH = 600;
		static const int SCREEN_HEIGHT = 800;

		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		void ClearBackBuffer();
		void Render();

		Graphics();
		~Graphics();

		bool Init();

	private:
		static Graphics* sInstance;
		static bool sInitialized;

		SDL_Window* mWindow = nullptr;
		SDL_Renderer* mRenderer = nullptr;
	};
}
