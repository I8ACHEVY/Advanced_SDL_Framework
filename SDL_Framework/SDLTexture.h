#pragma once
#include "Texture.h"

namespace SDL_Framework {
	class SDLTexture : public Texture {
	public:
		SDLTexture(std::string filename, bool managed = true);
		SDLTexture(std::string filename, int x, int y, int width, int height, bool managed = true);
		//The below constructor makes a TEXT object instead of using an image
		SDLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);

		~SDLTexture();

		void Render() override;
	private:

	};
}