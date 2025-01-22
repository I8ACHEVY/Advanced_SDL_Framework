#pragma once
#include "GLAnimatedTexture.h"
#include "InputManager.h"

using namespace SDL_Framework;

class CreditScreen : public GameEntity {
public:
	CreditScreen();
	~CreditScreen();

	void ChangeSelectedMode(int change);

	int SelectedMode();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	InputManager* mInputManager;

	GameEntity* mTopBar;
	GLTexture* mPart;
	GLTexture* mName;
	GLTexture* mCredit;

	GameEntity* mPlayModes;
	GLTexture* mStartMode;
	GLTexture* mOptionsMode;
	GLTexture* mHighScoreMode;
	GLTexture* mBackMode;
	GLTexture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	GLTexture* mTaito;
	GLTexture* mDates;
	GLTexture* mRights;
};
