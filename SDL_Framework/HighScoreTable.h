#pragma once
#include "GLAnimatedTexture.h"
#include "InputManager.h"

using namespace SDL_Framework;

class HighScoreTable : public GameEntity {
public:
	HighScoreTable();
	~HighScoreTable();

	void ChangeSelectedMode(int change);

	int SelectedMode();

	void Update() override;
	void Render() override;

private:

	InputManager* mInputManager;

	GameEntity* mTopBar;
	Texture* mVolume;
	Texture* mMute;
	Texture* mHighScores;

	GameEntity* mPlayModes;
	Texture* mStartMode;
	Texture* mOptionsMode;
	Texture* mBackMode;
	Texture* mCreditsMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffsetPos;
	int mSelectedMode;

	GameEntity* mBottomBar;
	Texture* mTaito;
	Texture* mDates;
	Texture* mRights;
};

