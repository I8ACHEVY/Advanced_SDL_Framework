#pragma once
#include "StartScreen.h"
#include "BackgroundStar.h"
#include "PlayScreen.h"
#include "OptionScreen.h"
#include "CreditScreen.h"
#include "HighScoreTable.h"


class ScreenManager {

public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();

	enum Screens { Start, Play, Option, Credit, HighScore };
	Screens mCurrentScreen;

	static ScreenManager* sInstance;

	AssetManager* mAssetManager;
	BackgroundStars* mBackgroundStars;
	InputManager* mInput;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	OptionScreen* mOptionScreen;
	CreditScreen* mCreditScreen;
	HighScoreTable* mHighScoreTable;
	//Graphics* mGraphic;

	//SDL_Texture* mBackground;
};