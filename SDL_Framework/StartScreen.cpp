#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayer1 = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayer2 = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });

	mTopBar->Parent(this);
	mPlayer1->Parent(mTopBar);
	mPlayer2->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayer1->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
	mPlayer2->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
	mHiScore->Position(-30, 0.0f);

	mLogoHolder = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
	mLogo = new Texture("GalagaLogo.png", 0, 0, 360, 180);

	mLogoHolder->Parent(this);
	mLogo->Parent(mLogoHolder);

	mLogo->Position(vec2_Zero);

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

	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mNamco = new Texture("namco", "namco__.ttf", 36, { 200, 0, 0 });
	mDates = new Texture("1981 - 1985 NAMCO) LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Position(vec2_Zero);
	mDates->Position(0.0f, 90.0f);
	mRights->Position(0.0f, 170.0f);
}

void StartScreen::Update() {

}

void StartScreen::Render() {
	mPlayer1->Render();
	mPlayer2->Render();
	mHiScore->Render();

	mLogo->Render();

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