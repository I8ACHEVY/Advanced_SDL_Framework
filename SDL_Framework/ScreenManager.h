#pragma once
#include "StartScreen.h"
#include "BackgroundStar.h"
#include "PlayScreen.h"


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

	AssetManager* mAssetManager;
	BackgroundStars* mBackgroundStars;
	InputManager* mInput;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	//Graphics* mGraphic;

	//SDL_Texture* mBackground;
};