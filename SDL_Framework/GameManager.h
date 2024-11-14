#pragma once
#include "Graphics.h"
#include "GameEntity.h"
#include "Timer.h"
#include "Texture.h"
#include "InputManager.h"

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
		
		//GameEntity* mParent;
		//GameEntity* mChild;

		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;

		Texture* mTex;
		Texture* mRedShip;

		SDL_Event mEvents;
	};
}