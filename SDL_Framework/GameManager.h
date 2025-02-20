#pragma once
#include "Graphics.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "GameEntity.h"
#include "AudioManager.h"
#include "PhysicsManager.h"

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

		//AnimatedTexture* mTex;
		//AnimatedTexture* mRedShip;

		Texture* mTex;
		Texture* mRedShip;

		PhysEntity* mPhys1;
		PhysEntity* mPhys2;
		PhysEntity* mPhys3;
		PhysEntity* mPhys4;

		Texture* mFontTex;

		SDL_Event mEvents;
	};
}