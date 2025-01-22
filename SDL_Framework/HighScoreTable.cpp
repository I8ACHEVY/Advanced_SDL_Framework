#include "HighScoreTable.h"

HighScoreTable::HighScoreTable() {
	mInputManager = InputManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 410.0f);
	//mPlayer1 = new Texture("1UP", "emulogic.ttf", 15, { 0, 255, 0 });
	//mPlayer2 = new Texture("2UP", "emulogic.ttf", 15, { 0, 255, 0 });
	mHighScores = new GLTexture("HighScore Table", "emulogic.ttf", 32, { 0, 255, 0 });

	mTopBar->Parent(this);
	//mPlayer1->Parent(mTopBar);
	//mPlayer2->Parent(mTopBar);
	mHighScores->Parent(mTopBar);

	//mPlayer1->Position(-Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
	//mPlayer2->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
	mHighScores->Position(0, 0.0f);

	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mStartMode = new GLTexture("Start", "emulogic.ttf", 15, { 230, 230, 230 });
	mOptionsMode = new GLTexture("Options", "emulogic.ttf", 15, { 230, 230, 230 });
	mCreditsMode = new GLTexture("Credits", "emulogic.ttf", 15, { 230, 230, 230 });
	mBackMode = new GLTexture("Back", "emulogic.ttf", 15, { 230, 230, 230 });
	mCursor = new GLTexture("Cursor.png");
	mCursor->Scale(Vector2(0.5f, 0.5f));

	mPlayModes->Parent(this);
	mStartMode->Parent(mPlayModes);
	mOptionsMode->Parent(mPlayModes);
	mCreditsMode->Parent(mPlayModes);
	mBackMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mStartMode->Position(0.0f, -28.0f);
	mOptionsMode->Position(0.0f, 0.0f);
	mCreditsMode->Position(0.0f, 30.0f);
	mBackMode->Position(0.0f, 60.0f);
	mCursor->Position(-90.0f, -28.0f);

	mSelectedMode = 0;
	mCursorOffsetPos = Vector2(0.0f, 29.0f);
	mCursorStartPos = mCursor->Position(Local);

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f);
	mTaito = new GLTexture("taito", "namco__.ttf", 15, { 0, 255, 0 });
	mDates = new GLTexture("1978 - 1997 taito corp.", "emulogic.ttf", 12, { 230, 230, 230 });
	mRights = new GLTexture("ALL RIGHTS RESERVED", "emulogic.ttf", 12, { 230, 230, 230 });

	mBottomBar->Parent(this);
	mTaito->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mTaito->Position(Vec2_Zero);
	mDates->Position(0.0f, 30.0f);
	mRights->Position(0.0f, 60.0f);

}

int HighScoreTable::SelectedMode() {
	return mSelectedMode;
}

void HighScoreTable::ChangeSelectedMode(int change) {
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

void HighScoreTable::Update() {

	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		ChangeSelectedMode(1);
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
		ChangeSelectedMode(-1);
	}
}

void HighScoreTable::Render() {

	//mPlayer1->Render();
	//mPlayer2->Render();
	mHighScores->Render();

	mStartMode->Render();
	mOptionsMode->Render();
	mCreditsMode->Render();
	mBackMode->Render();
	mCursor->Render();

	mTaito->Render();
	mDates->Render();
	mRights->Render();
}

HighScoreTable::~HighScoreTable() {

	delete mTopBar;
	mTopBar = nullptr;
	//delete mPlayer1;
	//mPlayer1 = nullptr;
	//delete mPlayer2;
	//mPlayer2 = nullptr;
	delete mHighScores;
	mHighScores = nullptr;

	delete mPlayModes;
	mPlayModes = nullptr;
	delete mStartMode;
	mStartMode = nullptr;
	delete mOptionsMode;
	mOptionsMode = nullptr;
	delete mCreditsMode;
	mCreditsMode = nullptr;
	delete mCreditsMode;
	mCreditsMode = nullptr;
	delete mBackMode;
	mBackMode = nullptr;
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