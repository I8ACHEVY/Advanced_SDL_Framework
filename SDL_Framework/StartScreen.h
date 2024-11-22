#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace SDL_Framework;

class StartScreen : public GameEntity {
public:
	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	InputManager* mInputManager;

	GameEntity* mTopBar;
	Texture* mPlayer1;
	Texture* mPlayer2;
	Texture* mHiScore;

	GameEntity* mLogoHolder;
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;

	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;
};
