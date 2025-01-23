#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

namespace SDL_Framework {
	class Texture : public GameEntity {
	public:
		Texture(std::string filename, bool managed = true);
		Texture(std::string filename, int x, int y, int width, 
			int height, bool managed = true);
		Texture(std::string text, std::string fontPath, int size, 
			SDL_Color color, bool managed = true);
		virtual ~Texture();

		Vector2 ScaledDimensions();

		void SetSourceRect(SDL_Rect* sourceRect);

		void Flip(bool hFlip, bool vFLip);

		virtual void Render() override;
	
	protected:
		SDL_Texture* mTex;
		Graphics* mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mSourceRect;
		SDL_Rect mDestinationRect;
		SDL_RendererFlip mFlip;

		void UpdateDstRect();
	};
}