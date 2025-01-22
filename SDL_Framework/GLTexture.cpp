#include "GLTexture.h"
#include "GLGraphics.h"

namespace SDL_Framework {
	GLTexture::GLTexture(std::string filename, bool managed) :
		Texture(filename, managed) {
		SetSurfaceTexture(filename, managed);

		Data = mSurface->pixels;

		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;

		mWidth = mSurface->w;
		mHeight = mSurface->h;
	}

	GLTexture::GLTexture(std::string filename, int x, int y,
		int w, int h, bool managed) :
		Texture(filename, x, y, w, h, managed) {
		SetSurfaceTexture(filename, managed);

		Data = mSurface->pixels;

		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;
	}

	GLTexture::GLTexture(std::string text, std::string fontPath,
		int size, SDL_Color color, bool managed) :
		Texture(text, fontPath, size, color, managed) {
		SetSurfaceTextTexture(text, fontPath, size, color, managed);

		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;

		mWidth = mSurface->w;
		mHeight = mSurface->h;
	}

	void GLTexture::Bind() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void GLTexture::SetSurfaceTexture(std::string filename, bool managed) {
		mSurface = AssetManager::Instance()->GetSurfaceTexture(filename, managed);

		if (mSurface != nullptr) {
			Generate();
		}
		else {
			std::cerr << "mSurface nullptr in SetSurfaceTexture!" << std::endl;
		}
	}

	void GLTexture::SetSurfaceTextTexture(std::string text, std::string filename,
		int size, SDL_Color color, bool managed) {
		mSurface = AssetManager::Instance()->GetSurfaceText(text, filename, size, color, managed);

		if (mSurface != nullptr) {
			Generate();
		}
		else {
			std::cerr << "mSurface nullptr in SetSurfaceTextTexture!" << std::endl;
		}
	}

	void GLTexture::Generate() {
		GLint mode;
		GLint nOfColors = mSurface->format->BytesPerPixel;

		if (nOfColors == 4) { //Contains an alpha channel
			if (mSurface->format->Rmask == 0x000000ff) { //this is a byte
				mode = GL_RGBA;
			}
			else {
				mode = GL_BGRA;
			}
		}
		else if (nOfColors == 3) { //no alpha channel
			if (mSurface->format->Rmask == 0x000000ff) { //this is a byte
				mode = GL_RGB;
			}
			else {
				mode = GL_BGR;
			}
		}
		else {
			mode = GL_RGBA;
		}

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		//Set texture wrapping/filtering options (on the currently bound texture object)
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Load and generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSurface->w, mSurface->h,
			0, GL_RGBA, GL_UNSIGNED_BYTE, mSurface->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	GLTexture::~GLTexture() {
	
		AssetManager::Instance()->DestroySurface(mSurface);
		mSurface = nullptr;
	}

	void GLTexture::Render() {
		UpdateDstRect();

		GLGraphics::Instance()->DrawSprite(this, mClipped ? &mSourceRect : nullptr,
			&mDestinationRect, Rotation(World), Flip);
	}
}