#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
mPlayer1 = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
mPlayer2 = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
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

mPlayer1->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
mPlayer2->Position(Graphics::SCREEN_WIDTH * 0.34f, 0.0f);
mHiScore->Position(0, 0.0f);
mPlayer1Score->Position(Graphics::SCREEN_WIDTH * -0.34f, 40.0f);
mPlayer2Score->Position(Graphics::SCREEN_WIDTH * 0.35f, 40.0f);
mTopScore->Position(Graphics::SCREEN_WIDTH * 0.08f, 40.0f);

mTopScore->Score(637982);

mLogoHolder = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
mLogo = new Texture("GalagaLogo.png", 0, 0, 360, 180);
mAnimatedLogo = new AnimatedTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.5f,
	AnimatedTexture::Vertical);

mLogoHolder->Parent(this);
mLogo->Parent(mLogoHolder);
mAnimatedLogo->Parent(mLogoHolder);

mLogo->Position(Vec2_Zero);
mAnimatedLogo->Position(Vec2_Zero);


mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230, 230, 230 });
mTwoPlayerMode = new Texture("2 Player", "emulogic.ttf", 32, { 230, 230, 230 });
mCursor = new Texture("Cursor.png");

mPlayModes->Parent(this);
mOnePlayerMode->Parent(mPlayModes);
mTwoPlayerMode->Parent(mPlayModes);
mCursor->Parent(mPlayModes);

mOnePlayerMode->Position(0.0f, -35.0f);
mTwoPlayerMode->Position(0.0f, 35.0f);
mCursor->Position(-175.0f, -35.0f);

mSelectedMode = 0;
mCursorOffsetPos = Vector2(0.0f, 70.0f);
mCursorStartPos = mCursor->Position(Local);

mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
mNamco = new Texture("namco", "namco__.ttf", 36, { 200, 0, 0 });
mDates = new Texture("1981 - 1985 NAMCO) LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

mBottomBar->Parent(this);
mNamco->Parent(mBottomBar);
mDates->Parent(mBottomBar);
mRights->Parent(mBottomBar);

mNamco->Position(Vec2_Zero);
mDates->Position(0.0f, 90.0f);
mRights->Position(0.0f, 170.0f);

Position(mAnimationStartPos);
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}
	else if (mSelectedMode > 1) {
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

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
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
	delete mOnePlayerMode;
	mOnePlayerMode = nullptr;
	delete mTwoPlayerMode;
	mTwoPlayerMode = nullptr;
	delete mCursor;
	mCursor = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mNamco = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mRights;
	mRights = nullptr;

	mTimer = nullptr;
	mInputManager = nullptr;
}