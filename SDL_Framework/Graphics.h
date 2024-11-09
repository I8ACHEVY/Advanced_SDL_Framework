#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include<string>

namespace SDL_Framework
{
	class Graphics{
	public:
		static const int SCREEN_WIDTH = 600;
		static const int SCREEN_HEIGHT = 800;

		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);
		void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, 
			SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

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
