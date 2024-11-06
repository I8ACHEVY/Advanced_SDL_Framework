#include "Graphics.h"

namespace SDLFramework
{
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	Graphics* Graphics::Instance() { // make this class a singleton
		if (sInstance == nullptr) {
			sInstance = new Graphics();
		}
		return sInstance;
	}

	void Graphics::Release() {
		delete sInstance;
		sInstance = nullptr;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	Graphics();
	~Graphics();

	bool Init();


	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

}