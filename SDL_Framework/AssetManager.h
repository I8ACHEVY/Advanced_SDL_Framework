#pragma once
#include "Graphics.h"
#include "ShaderUtil.h"
#include <SDL_mixer.h>
#include <map>
#include <sstream>

namespace SDL_Framework {
	class AssetManager {
	public:
		static AssetManager* Instance();
		static void Release();

		ShaderUtil GetShaderUtil(std::string name);
		void LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile,
			const GLchar* gShaderFile = nullptr, std::string name = "Default");

		SDL_Texture* GetTexture(std::string filename, bool managed = true);
		SDL_Texture* GetText(std::string text, std::string filename, int size,
			SDL_Color color, bool managed = true);

		Mix_Music* GetMusic(std::string filename, bool managed = true);	//Mix_LoadMUS
		Mix_Chunk* GetSFX(std::string filename, bool managed = true);		//Mix_LoadWAV

		SDL_Surface* GetSurfaceTexture(std::string filename, bool managed = true);
		SDL_Surface* GetSurfaceText(std::string text, std::string filename,
			int size, SDL_Color color, bool managed = true);

		void DestroyTexture(SDL_Texture* texture);
		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);
		void DestroySurface(SDL_Surface* surface);

	private:
		AssetManager();
		~AssetManager();

		void UnloadTexture(SDL_Texture* texture);
		void UnloadSurface(SDL_Surface* surface);
		void UnloadMusic(Mix_Music* music);
		void UnloadSFX(Mix_Chunk* sfx);

		TTF_Font* GetFont(std::string filename, int size);

		static AssetManager* sInstance;

		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, SDL_Surface*> mSurfaceTextures;
		std::map<std::string, TTF_Font*> mFonts;
		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;

		std::map<std::string, SDL_Texture*> mText;
		std::map<std::string, SDL_Surface*> mSurfaceText;

		std::map<std::string, ShaderUtil> mShaders;

		std::map<Mix_Music*, unsigned int> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned int> mSFXRefCount;
		std::map<SDL_Texture*, unsigned int> mTextureRefCount;
		std::map<SDL_Surface*, unsigned> mSurfaceRefCount;
	};
}

