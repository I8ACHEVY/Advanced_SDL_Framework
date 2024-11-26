#pragma once
#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>
#include <sstream>

namespace SDL_Framework {
	class AssetManager {
	public:
		static AssetManager* Instance();
		static void Release();

		SDL_Texture* GetTexture(std::string filename, bool managed = true);
		SDL_Texture* GetText(std::string text, std::string filename, int size,
			SDL_Color color, bool managed = true);

		Mix_Music* GetMusic(std::string filename, bool managed = true);	//Mix_LoadMUS
		Mix_Chunk* GetSFX(std::string filename, bool managed = true);		//Mix_LoadWAV

		void DestroyTexture(SDL_Texture* texture);
		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);

	private:
		AssetManager();
		~AssetManager();

		void UnloadTexture(SDL_Texture* texture);
		void UnloadMusic(Mix_Music* music);
		void UnloadSFX(Mix_Chunk* sfx);

		TTF_Font* GetFont(std::string filename, int size);

		static AssetManager* sInstance;

		std::map<std::string, SDL_Texture*> mTextures;

		std::map<std::string, TTF_Font*> mFonts;
		//std::map<std::string, SDL_Texture*> mText;

		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;

		std::map<Mix_Music*, unsigned int> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned int> mSFXRefCount;

		std::map<SDL_Texture*, unsigned int> mTextureRefCount;
	};
}

