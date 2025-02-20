#include "Texture.h"

namespace SDL_Framework {
	Texture::Texture(std::string filename, bool managed) {
		mGraphics = Graphics::Instance();

		mTex = AssetManager::Instance()->GetTexture(filename, managed);
		mRedShip = AssetManager::Instance()->GetTexture(filename, managed);

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);
		SDL_QueryTexture(mRedShip, nullptr, nullptr, &mWidth, &mHeight);

		mClipped = false;
		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	Texture::Texture(std::string filename, int x, int y, int width, int height, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename, managed);
		mRedShip = AssetManager::Instance()->GetTexture(filename, managed);

		mWidth = width;
		mHeight = height;

		mClipped = true;

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;

		mSourceRect.x = x;
		mSourceRect.y = y;
		mSourceRect.w = width;
		mSourceRect.h = height;
	}

	Texture::Texture(std::string text, std::string fontPath, int size, 
		SDL_Color color, bool managed){
		mGraphics = Graphics::Instance();

		mTex = AssetManager::Instance()->GetText(text, fontPath,
			size, color, managed);
		mRedShip = AssetManager::Instance()->GetText(text, fontPath,
			size, color, managed);

		mClipped = false;

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);
		SDL_QueryTexture(mRedShip, nullptr, nullptr, &mWidth, &mHeight);

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;

	}

	Texture::~Texture() {
		AssetManager::Instance()->DestroyTexture(mTex);
		AssetManager::Instance()->DestroyTexture(mRedShip);
		mTex = nullptr;
		mRedShip = nullptr;
		mGraphics = nullptr;
	}

	Vector2 Texture::ScaledDimensions() {
		Vector2 scaledDimensions = Scale();
		scaledDimensions.x *= mWidth;
		scaledDimensions.y *= mHeight;

		return scaledDimensions;
	}

	void Texture::SetSourceRect(SDL_Rect* sourceRect) {
		mSourceRect = *sourceRect;
	}

	void Texture::Render() {
		Vector2 pos = Position(World);
		Vector2 scale = Scale(World);

		mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
		mDestinationRect.w = (int)(mWidth * scale.x);
		mDestinationRect.h = (int)(mHeight * scale.y);

		mGraphics->DrawTexture(mTex, mClipped ?  &mSourceRect : nullptr, &mDestinationRect, Rotation(World));

		mGraphics->DrawTexture(mRedShip, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
	}
}