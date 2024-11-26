#pragma once
#include "Graphics.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "StartScreen.h"
#include "Random.h"
#include "BackgroundStar.h"

namespace SDL_Framework {
	class GameManager {
	public:
		static GameManager* Instance();
		static void Release();

		GameManager();
		~GameManager();

		void Update();
		void LateUpdate();

		void Render();

		void Run();

	private:
		const int FRAME_RATE = 60;
		static GameManager* sInstance;
		bool mQuit;

		float mScaleTimeZ;
		float mScaleTimeC;

		float mScaleTimeM;
		float mScaleTimePER;

		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;
		Random* mRandom;
		BackgroundStars* mBackgroundStars;

		StartScreen* mStartScreen;

		SDL_Event mEvents;
	};
}