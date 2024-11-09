#pragma once
#include "Graphics.h"
#include "Timer.h"

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
		
		GameEntity* mParent;
		mChild;

		Graphics* mGraphics;
		Timer* mTimer;

		SDL_Event mEvents;
	};
}