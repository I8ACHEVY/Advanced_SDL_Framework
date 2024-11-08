#include "Timer.h"

namespace SDL_Framework {

	Timer* Timer::sInstance = nullptr;

	Timer* Timer::Instance() {
		if (sInstance == nullptr) {
			sInstance = new Timer();
		}
		return sInstance;
	}
	void Timer::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void Timer::Reset() {
		mStartTicks = SDL_GetTicks(); // get performance counter?
	}

	float Timer::DeltaTime() const{
		return mDeltaTime;
	}

	void Timer::TimeScale(float ts) {
		mTimeScale = ts;
	}

	float Timer::TimeScale() const{
		return mTimeScale;
	}

	void Timer::Update() {		//get performance frequency?
		mElapsedTicks = SDL_GetTicks() - mStartTicks;  // calc diff in time in m/s 
		mDeltaTime = mElapsedTicks * 0.001f;			// convert from m/s to seconds
	}

	Timer::Timer() {
		Reset();
		mElapsedTicks = 0;
		mDeltaTime = 0.0f;
		mTimeScale = 1.0f;
	}

	Timer::~Timer() {

	}

}