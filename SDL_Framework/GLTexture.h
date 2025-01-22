#pragma once
#include <glew.h>
#include "Texture.h"

namespace SDL_Framework {

	class GLTexture : public Texture {
	public:
		GLuint ID;
		GLuint Width, Height;
		GLuint Internal_Format;
		GLuint Image_Format;
		GLuint WrapS;
		GLuint WrapT;
		GLuint FilterMin;
		GLuint FilterMag;
		int mode;
		bool rendered;
		void* Data;
		SDL_RendererFlip Flip;
		SDL_Surface* mSurface;

		GLTexture(std::string filename, bool managed = true);
		GLTexture(std::string filename, int x, int y, int width, int height, bool managed = true);
		//The below constructor makes a TEXT object instead of using an image
		GLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);

		void SetSurfaceTexture(std::string filename, bool managed = true);
		void SetSurfaceTextTexture(std::string text, std::string filename,
			int size, SDL_Color color, bool managed = true);

		void Generate();
		void Bind();

		~GLTexture();

		virtual void Render() override;
	};
}
