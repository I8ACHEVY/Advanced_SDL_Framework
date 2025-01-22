#include "CreditScreen.h"

CreditScreen::CreditScreen() {
	mInputManager = InputManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 410.0f);
	mPart = new GLTexture("Created by: ", "emulogic.ttf", 15, { 0, 255, 0 });
	mName = new GLTexture("Tomohiro Nishikado", "emulogic.ttf", 15, { 0, 255, 0 });
	mCredit = new GLTexture("Credits", "emulogic.ttf", 32, { 0, 255, 0 });

	mTopBar->Parent(this);
	mPart->Parent(mTopBar);
	mName->Parent(mTopBar);
	mCredit->Parent(mTopBar);

	mPart->Position(-Graphics::SCREEN_WIDTH * 0.1f, 50.0f);
	mName->Position(Graphics::SCREEN_WIDTH * 0.1f, 50.0f);
	mCredit->Position(0, 0.0f);

	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mStartMode = new GLTexture("Start", "emulogic.ttf", 15, { 230, 230, 230 });
	mOptionsMode = new GLTexture("Options", "emulogic.ttf", 15, { 230, 230, 230 });
	mHighScoreMode = new GLTexture ("HighScores", "emulogic.ttf", 15, { 230, 230, 230 });
	mBackMode = new GLTexture("Back", "emulogic.ttf", 15, { 230, 230, 230 });
	mCursor = new GLTexture("Cursor.png");
	mCursor->Scale(Vector2(0.5f, 0.5f));

	mPlayModes->Parent(this);
	mStartMode->Parent(mPlayModes);
	mOptionsMode->Parent(mPlayModes);
	mHighScoreMode->Parent(mPlayModes);
	mBackMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mStartMode->Position(0.0f, -28.0f);
	mOptionsMode->Position(0.0f, 0.0f);
	mHighScoreMode->Position(0.0f, 30.0f);
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

int CreditScreen::SelectedMode() {
	return mSelectedMode;
}

void CreditScreen::ChangeSelectedMode(int change) {
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

void CreditScreen::Update() {

	if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
		ChangeSelectedMode(1);
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
		ChangeSelectedMode(-1);
	}
}

void CreditScreen::Render() {

	mPart->Render();
	mName->Render();
	mCredit->Render();

	mStartMode->Render();
	mOptionsMode->Render();
	mHighScoreMode->Render();
	mBackMode->Render();
	mCursor->Render();

	mTaito->Render();
	mDates->Render();
	mRights->Render();
}

CreditScreen::~CreditScreen() {

	delete mTopBar;
	mTopBar = nullptr;
	delete mPart;
	mPart = nullptr;
	delete mName;
	mName = nullptr;
	delete mCredit;
	mCredit = nullptr;

	delete mPlayModes;
	mPlayModes = nullptr;
	delete mStartMode;
	mStartMode = nullptr;
	delete mOptionsMode;
	mOptionsMode = nullptr;
	delete mHighScoreMode;
	mHighScoreMode = nullptr;
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