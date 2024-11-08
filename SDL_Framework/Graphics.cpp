#include "Graphics.h"

namespace SDL_Framework
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

	Graphics::Graphics() : mRenderer(nullptr), mWindow(nullptr){
		sInitialized = Init();
	}
	Graphics::~Graphics() {
		// Destroy renderer
		SDL_DestroyRenderer(mRenderer);
		//Destroy the window
		SDL_DestroyWindow(mWindow);
	}

	bool Graphics::Init() {
		// Initialize SDL subsystem
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){
			std::cerr << "SDL could not init, error: " << SDL_GetError() 
				      << std::endl;
			return false;
		}

		std::cout << "STL Advanced Framework\n";

		mWindow = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (mWindow == nullptr)
		{
			std::cerr << "Unable to create a window. SDL_Error: "
				      << SDL_GetError() << std::endl;
			return false; //end if window creations fails
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == nullptr)
		{
			std::cerr << "Unable to get renderer. SDL_Error: "
				      << SDL_GetError() << std::endl;
			SDL_DestroyWindow(mWindow); // cleanup window before returning
			return false;
		}
		return true;
	}
}