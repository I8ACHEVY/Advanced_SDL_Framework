#include "SDLTexture.h"

namespace SDL_Framework {
	SDLTexture::SDLTexture(std::string text, std::string fontPath, int size,
		SDL_Color color, bool managed) :
		Texture(text, fontPath, size, color, managed) {
	}

	SDLTexture::SDLTexture(std::string filename, int x, int y, int w, int h,
		bool managed) : Texture(filename, x, y, w, h, managed) {
	}

	SDLTexture::SDLTexture(std::string filename, bool managed) :
		Texture(filename, managed) {
	}

	SDLTexture::~SDLTexture() {}

	void SDLTexture::Render() {
		Texture::Render();
	}

}