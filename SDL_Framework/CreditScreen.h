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
	Texture* mPart;
	Texture* mName;
	Texture* mCredit;

	GameEntity* mPlayModes;
	Texture* mStartMode;
	Texture* mOptionsMode;
	Texture* mHighScoreMode;
	Texture* mBackMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	Texture* mTaito;
	Texture* mDates;
	Texture* mRights;
};
