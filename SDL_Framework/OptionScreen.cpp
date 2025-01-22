#include "OptionScreen.h"

OptionScreen::OptionScreen() {

	mInputManager = InputManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 430.0f);
	mVolume = new Texture("Volume: Use - or + to change Volume Level", "emulogic.ttf", 15, { 0, 255, 0 });
	mMute = new Texture("Mute: Use M to mute and unmute audio", "emulogic.ttf", 15, { 0, 255, 0 });
	mOptMenu = new Texture("Options Menu", "emulogic.ttf", 32, { 0, 255, 0 });

	mTopBar->Parent(this);
	mVolume->Parent(mTopBar);
	mMute->Parent(mTopBar);
	mOptMenu->Parent(mTopBar);

	mVolume->Position(0.0f, 60.0f);
	mMute->Position(0.0f, 100.0f);
	mOptMenu->Position(0, 0.0f);

	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mStartMode = new Texture("Start", "emulogic.ttf", 15, { 230, 230, 230 });
	mCreditsMode = new Texture("Credits", "emulogic.ttf", 15, { 230, 230, 230 });
	mHighScoreMode = new Texture("HighScores", "emulogic.ttf", 15, { 230, 230, 230 });
	mBackMode = new Texture("Back", "emulogic.ttf", 15, { 230, 230, 230 });
	mCursor = new Texture("Cursor.png");
	mCursor->Scale(Vector2(0.5f, 0.5f));

	mPlayModes->Parent(this);
	mStartMode->Parent(mPlayModes);
	mCreditsMode->Parent(mPlayModes);
	mHighScoreMode->Parent(mPlayModes);
	mBackMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mStartMode->Position(0.0f, -28.0f);
	mCreditsMode->Position(0.0f, 0.0f);
	mHighScoreMode->Position(0.0f, 30.0f);
	mBackMode->Position(0.0f, 60.0f);
	mCursor->Position(-90.0f, -28.0f);

	mSelectedMode = 0;
	mCursorOffsetPos = Vector2(0.0f, 29.0f);
	mCursorStartPos = mCursor->Position(Local);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);
	mTaito = new Texture("taito", "namco__.ttf", 15, { 0, 255, 0 });
	mDates = new Texture("1978 - 1997 taito corp.", "emulogic.ttf", 12, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 12, { 230, 230, 230 });

	mBottomBar->Parent(this);
	mTaito->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mTaito->Position(Vec2_Zero);
	mDates->Position(0.0f, 30.0f);
	mRights->Position(0.0f, 60.0f);

}

int OptionScreen::SelectedMode() {
	return mSelectedMode;
}

void OptionScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 3;
	}
	else if (mSelectedMode > 3) {
		mSelectedMode = 0;
	}

	mCursor->Position(mCursorStartPos + mCursorOffsetPos *
		(float)mSelectedMode);

}

void OptionScreen::Update() {

	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		ChangeSelectedMode(1);
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
		ChangeSelectedMode(-1);
	}
}

void OptionScreen::Render() {

	mVolume->Render();
	mMute->Render();
	mOptMenu->Render();

	mStartMode->Render();
	mBackMode->Render();
	mCreditsMode->Render();
	mHighScoreMode->Render();
	mCursor->Render();

	mTaito->Render();
	mDates->Render();
	mRights->Render();
}

OptionScreen::~OptionScreen() {

	delete mTopBar;
	mTopBar = nullptr;
	delete mVolume;
	mVolume = nullptr;
	delete mMute;
	mMute = nullptr;
	delete mOptMenu;
	mOptMenu = nullptr;

	delete mPlayModes;
	mPlayModes = nullptr;
	delete mStartMode;
	mStartMode = nullptr;
	delete mBackMode;
	mBackMode = nullptr;
	delete mCreditsMode;
	mCreditsMode = nullptr;
	delete mHighScoreMode;
	mHighScoreMode = nullptr;
	delete mCursor;
	mCursor = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
	delete mTaito;
	mTaito = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mRights;
	mRights = nullptr;

	mInputManager = nullptr;
}