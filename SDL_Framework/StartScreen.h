#pragma once
#include "GLAnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"

using namespace SDL_Framework;

class StartScreen : public GameEntity {
public:
	StartScreen();
	~StartScreen();

	void ChangeSelectedMode(int change);

	void ResetAnimation();

	int SelectedMode();

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
	Scoreboard* mPlayer1Score;
	Scoreboard* mPlayer2Score;
	Scoreboard* mTopScore;

	GameEntity* mLogoHolder;
	Texture* mLogo;
	GLAnimatedTexture* mAnimatedLogo;

	GameEntity* mPlayModes;
	Texture* mStartMode;
	Texture* mOptionsMode;
	Texture* mCreditsMode;
	Texture* mHighScoreMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	Texture* mTaito;
	Texture* mDates;
	Texture* mRights;
};
