#include "AudioManager.h"

namespace SDL_Framework {

	AudioManager* AudioManager::sInstance = nullptr;

	AudioManager* AudioManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AudioManager();
		}
		return sInstance;
	}

	void AudioManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void AudioManager::PlayMusic(std::string filename, int loops) {
		Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
	}

	void AudioManager::PlayMusic(Mix_Music* music, int loops) {
		Mix_PlayMusic(music, loops);
	}

	void AudioManager::PauseMusic() {
		if (Mix_PlayingMusic() != 0) {
			Mix_PauseMusic();
		}
	}

	void AudioManager::ResumeMusic() {
		if (Mix_PausedMusic() != 0) {
			Mix_ResumeMusic();
		}
	}

	void AudioManager::MusicVolume(int volume) {		// max = 128
		if (volume < 0) {
			volume = 0;
		}
		else if (volume > MIX_MAX_VOLUME) {
			volume = MIX_MAX_VOLUME;
		}
		Mix_VolumeMusic(volume);
	}

	void AudioManager::SFXVolume(int volume) {
		if (volume < 0) {
			volume = 0;
		}
		else if (volume > MIX_MAX_VOLUME) {
			volume = MIX_MAX_VOLUME;
		}

		for (int i = 0; i < MIX_CHANNELS; i++) {
			Mix_Volume(i, volume);
		}
	}

	void AudioManager::IncreaseVolume() {
		int currentMusicVolume = Mix_VolumeMusic(-1);
		int newMusicVolume = currentMusicVolume + 10;
		if (newMusicVolume > MIX_MAX_VOLUME) newMusicVolume = MIX_MAX_VOLUME;
		MusicVolume(newMusicVolume);

		int currentSFXVolume = Mix_Volume(-1, -1);
		int newSFXVolume = currentSFXVolume + 10;
		if (newSFXVolume > MIX_MAX_VOLUME) newSFXVolume = MIX_MAX_VOLUME;
		SFXVolume(newSFXVolume);
	}

	void AudioManager::DecreaseVolume() {
		int currentMusicVolume = Mix_VolumeMusic(-1);
		int newMusicVolume = currentMusicVolume - 10;
		if (newMusicVolume < 0) newMusicVolume = 0;
		MusicVolume(newMusicVolume);

		int currentSFXVolume = Mix_Volume(-1, -1);
		int newSFXVolume = currentSFXVolume - 10;
		if (newSFXVolume < 0) newSFXVolume = 0;
		SFXVolume(newSFXVolume);
	}

	bool AudioManager::Muted() {
		return isMuted;
	}

	void AudioManager::Mute() {
		if (!isMuted) {
			previousMusicVolume = Mix_VolumeMusic(-1);
			previousSFXVolume = Mix_Volume(-1, -1);
			MusicVolume(0);
			SFXVolume(0);
			isMuted = true;
		}
	}

	void AudioManager::Unmute() {
		if (isMuted) {
			MusicVolume(previousMusicVolume);
			SFXVolume(previousSFXVolume);
			isMuted = false;
		}
	}

	void AudioManager::PlaySFX(std::string filename, int loops, int channel) {
		Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loops);
	}

	void AudioManager::PlaySFX(Mix_Chunk* sfx, int loops, int channel) {
		Mix_PlayChannel(channel, sfx, loops);
	}

	AudioManager::AudioManager() {
		mAssetManager = AssetManager::Instance();

		if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
			std::cerr << "Unable to initialize SDL Audio! SDL Error: " << SDL_GetError()
				<< std::endl;
			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
			std::cerr << "Unable to initialize Audio Mix Error: " << Mix_GetError() << std::endl;
			return;
		}
	}

	AudioManager::~AudioManager() {
		mAssetManager = nullptr;
		Mix_CloseAudio();
		Mix_Quit();
	}


}