#pragma once
#include "Graphics.h"

namespace SDL_Framework {
	class SDLGraphics : public Graphics {
	public:
		static SDLGraphics* Instance();

		SDLGraphics();
		~SDLGraphics();

		void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dst_Rect = nullptr,
			float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

		void Render() override;
		void ClearBackBuffer() override;

	private:

		bool Init() override;
	};

}
