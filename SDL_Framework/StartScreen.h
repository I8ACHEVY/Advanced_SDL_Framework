#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace SDL_Framework;

class StartScreen : public GameEntity {
public:
	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int change);

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	InputManager* mInputManager;

	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

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
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;
};
