#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT * 0.5f);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 410.0f);
mPlayer1 = new GLTexture("1UP", "emulogic.ttf", 15, { 0, 255, 0 });
mPlayer2 = new GLTexture("2UP", "emulogic.ttf", 15, { 0, 255, 0 });
mHiScore = new GLTexture("HI SCORE", "emulogic.ttf", 15, { 0, 255, 0 });
mPlayer1Score = new Scoreboard({ 255, 255, 255 });
mPlayer2Score = new Scoreboard({ 255, 255, 255 });
mTopScore = new Scoreboard();

mTopBar->Parent(this);
mPlayer1->Parent(mTopBar);
mPlayer2->Parent(mTopBar);
mHiScore->Parent(mTopBar);
mPlayer1Score->Parent(mTopBar);
mPlayer2Score->Parent(mTopBar);
mTopScore->Parent(mTopBar);

mPlayer1->Position(-Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
mPlayer2->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
mHiScore->Position(0, 0.0f);
mPlayer1Score->Position(Graphics::SCREEN_WIDTH * -0.19f, 30.0f);
mPlayer2Score->Position(Graphics::SCREEN_WIDTH * 0.21f, 30.0f);
mTopScore->Position(Graphics::SCREEN_WIDTH * 0.045f, 30.0f);

mTopScore->Score(645987);	//CREATE SAVE SYSTEM

mLogoHolder = new GameEntity(Graphics::SCREEN_WIDTH * 0.49f, Graphics::SCREEN_HEIGHT * 0.55f);
mLogo = new GLTexture("InvaderSprites.png", -10, 0, 520, 184);
mAnimatedLogo = new GLAnimatedTexture("InvaderSprites.png", -10, 0, 520, 184, 0, 0.5f,
	Animation::Layouts::Vertical);

mLogoHolder->Parent(this);
mLogo->Parent(mLogoHolder);
mAnimatedLogo->Parent(mLogoHolder);

mLogo->Position(Vec2_Zero);
mAnimatedLogo->Position(Vec2_Zero);


mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
mStartMode = new GLTexture("Start", "emulogic.ttf", 15, { 230, 230, 230 });
mOptionsMode = new GLTexture("Options", "emulogic.ttf", 15, { 230, 230, 230 });
mCreditsMode = new GLTexture("Credits", "emulogic.ttf", 15, { 230, 230, 230 });
mHighScoreMode = new GLTexture("HighScores", "emulogic.ttf", 15, { 230, 230, 230 });
mCursor = new GLTexture("Cursor.png");
mCursor->Scale(Vector2(0.5f, 0.5f));

mPlayModes->Parent(this);
mStartMode->Parent(mPlayModes);
mOptionsMode->Parent(mPlayModes);
mCreditsMode->Parent(mPlayModes);
mHighScoreMode->Parent(mPlayModes);
mCursor->Parent(mPlayModes);

mStartMode->Position(0.0f, -28.0f);
mOptionsMode->Position(0.0f, 0.0f);
mCreditsMode->Position(0.0f, 30.0f);
mHighScoreMode->Position(0.0f, 60.0f);
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

ResetAnimation();
}

void StartScreen::ResetAnimation() {
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Position(mAnimationStartPos);
}

int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
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

void StartScreen::Update() {
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Position(Lerp(mAnimationStartPos, mAnimationEndPos,
			mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN) ||
			mInputManager->KeyPressed(SDL_SCANCODE_UP)) {

			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else {
		mAnimatedLogo->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render() {

	mPlayer1->Render();
	mPlayer2->Render();
	mHiScore->Render();
	mPlayer1Score->Render();
	mPlayer2Score->Render();
	mTopScore->Render();

	if (!mAnimationDone) {
		mLogo->Render();
	}
	else {
		mAnimatedLogo->Render();
	}

	mStartMode->Render();
	mOptionsMode->Render();
	mCreditsMode->Render();
	mHighScoreMode->Render();
	mCursor->Render();

	mTaito->Render();
	mDates->Render();
	mRights->Render();
}

StartScreen::~StartScreen() {

	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayer1;
	mPlayer1 = nullptr;
	delete mPlayer2;
	mPlayer2 = nullptr;
	delete mHiScore;
	mHiScore = nullptr;
	delete mPlayer1Score;
	mPlayer1Score = nullptr;
	delete mPlayer2Score;
	mPlayer2Score = nullptr;
	delete mTopScore;
	mTopScore = nullptr;

	delete mLogoHolder;
	mLogoHolder = nullptr;
	delete mLogo;
	mLogo = nullptr;
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;

	delete mPlayModes;
	mPlayModes = nullptr;
	delete mStartMode;
	mStartMode = nullptr;
	delete mOptionsMode;
	mOptionsMode = nullptr;
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

	mTimer = nullptr;
	mInputManager = nullptr;
}