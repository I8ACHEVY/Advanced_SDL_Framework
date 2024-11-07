#pragma once
#include <SDL.h>

namespace SDL_Framework {
	class Timer {

	public:
		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime() const;

		void TimeScale(float timeScale);
		float TimeScale() const;

		void Update();

		Timer();
		~Timer();

	private:
		static Timer* sInstance;
		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float mTimeScale;
	};
}