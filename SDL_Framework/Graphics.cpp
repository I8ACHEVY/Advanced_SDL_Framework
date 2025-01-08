#include "Graphics.h"

namespace SDL_Framework
{
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	Graphics* Graphics::Instance() { 
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

	SDL_Texture* Graphics::LoadTexture(std::string path) {
		SDL_Texture* tex = nullptr;

		SDL_Surface* surface = IMG_Load(path.c_str());

		if (surface == nullptr) {
			std::cerr << "unable to load " << path << ". IMG Error: "
				<< IMG_GetError() << std::endl;
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (tex == nullptr) {
			std::cerr << "Unable to create texture from surface. IMG Error: "
				<< IMG_GetError() << std::endl;
			SDL_FreeSurface(surface);
			return nullptr;
		}
		return tex;
	}

	void Graphics::DrawLine(float startX, float startY, float endX, float endY) {
		SDL_Color color;
		SDL_GetRenderDrawColor(mRenderer, &color.r, &color.g, &color.b, &color.a);
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(mRenderer, (int)startX, (int)startY, (int)endX, (int)endY);
		SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
	}

	void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect,
		float angle, SDL_RendererFlip flip) {
		SDL_RenderCopyEx(mRenderer, texture, srcRect, dstRect, angle, nullptr, flip);
	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (surface == nullptr) {
			std::cerr << "CreateTextTexture:: TTF_RenderText_Solid Error: " 
					  << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

		if (tex == nullptr) {
			std::cerr << "CreateTextTexture:: SDL_CreateTextureFromSurface Error: "
				      << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(surface);
		return tex;
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
		
		SDL_DestroyRenderer(mRenderer);
		
		SDL_DestroyWindow(mWindow);
	}

	bool Graphics::Init() {
		
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){
			std::cerr << "SDL could not init, error: " << SDL_GetError() 
				      << std::endl;
			return false;
		}

		std::cout << "STL Advanced Framework\n";

		mWindow = SDL_CreateWindow(
			WINDOW_TITLE,
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
			return false; 
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == nullptr)
		{
			std::cerr << "Unable to get renderer. SDL_Error: "
				      << SDL_GetError() << std::endl;
			SDL_DestroyWindow(mWindow); 
			return false;
		}

		//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);		//Change background to white for debug positioning

		if (TTF_Init() == -1) {
			std::cerr << "Unable to initialize SDL_TTF, TTF Error: " << TTF_GetError()
				<< std::endl;
			return false;
		}

		return true;
	}
}