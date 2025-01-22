#pragma once
#include "GLAnimatedTexture.h"
#include "InputManager.h"

using namespace SDL_Framework;

class OptionScreen : public GameEntity {
public:
	OptionScreen();
	~OptionScreen();

	void ChangeSelectedMode(int change);

	int SelectedMode();

	void Update() override;
	void Render() override;

private:

	InputManager* mInputManager;

	GameEntity* mTopBar;
	GLTexture* mVolume;
	GLTexture* mMute;
	GLTexture* mOptMenu;

	GameEntity* mPlayModes;
	GLTexture* mStartMode;
	GLTexture* mBackMode;
	GLTexture* mCreditsMode;
	GLTexture* mHighScoreMode;
	GLTexture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	GLTexture* mTaito;
	GLTexture* mDates;
	GLTexture* mRights;
};

