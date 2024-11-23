#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

namespace SDL_Framework
{
	class Graphics{
	public:
		static const int SCREEN_WIDTH = 1024;
		static const int SCREEN_HEIGHT = 896;
		const char* WINDOW_TITLE = "Galaga";

		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);

		void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, 
			SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

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
