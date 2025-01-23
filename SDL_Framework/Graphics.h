#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm.hpp>

namespace SDL_Framework
{
	class GLTexture;
	class Graphics{
	public:
		enum class RenderMode {
			SDL,
			GL
		};

		static const int SCREEN_WIDTH = 1070;
		static const int SCREEN_HEIGHT = 1040;
		const char* WINDOW_TITLE = "Space Invaders";

		static void SetMode(RenderMode mode);
		static Graphics* Instance();
		static void Release();
		static bool Initialized();


		virtual void DrawSprite(GLTexture* texture, SDL_Rect* srcRect = nullptr, 
			SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) {}
		virtual void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, 
			SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void DrawLine(float startX, float startY, float endX, float endY);

		virtual void ClearBackBuffer();
		virtual void Render();

		SDL_Texture* LoadTexture(std::string path);
		SDL_Surface* LoadSurface(std::string path);
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		SDL_Surface* CreateTextSurface(TTF_Font* font, std::string text, SDL_Color color);

	protected:
		static Graphics* sInstance;
		static bool sInitialized;
		static RenderMode sMode;

		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		SDL_GLContext mGLContext;

		Graphics();
		~Graphics();

		virtual bool Init();

	};
}
