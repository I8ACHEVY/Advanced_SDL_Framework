#include "SDLGraphics.h"

namespace SDL_Framework {
	SDLGraphics* SDLGraphics::Instance() {
		if (sInstance == nullptr) {
			Graphics::Instance();
		}

		return static_cast<SDLGraphics*>(sInstance);
	}

	SDLGraphics::SDLGraphics() : Graphics() {
		//TODO: Look into why this creates a second screen
		//sInitialized = Init();
	}

	SDLGraphics::~SDLGraphics() {}

	void SDLGraphics::DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dst_Rect,
		float angle, SDL_RendererFlip flip) {
		SDL_RenderCopyEx(mRenderer, texture, srcRect, dst_Rect, angle, nullptr, flip);
	}

	void SDLGraphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	void SDLGraphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	bool SDLGraphics::Init() {
		return Graphics::Init();
	}
}