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
	Texture* mVolume;
	Texture* mMute;
	Texture* mOptMenu;

	GameEntity* mPlayModes;
	Texture* mStartMode;
	Texture* mBackMode;
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

