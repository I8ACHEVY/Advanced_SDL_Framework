#pragma once
#include "StartScreen.h"
#include "BackgroundStar.h"


class ScreenManager {


public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();

	enum Screens { Start, Play };
	Screens mCurrentScreen;

	static ScreenManager* sInstance;
	
	BackgroundStars* mBackgroundStars;
	InputManager* mInput;

	StartScreen* mStartScreen;
};