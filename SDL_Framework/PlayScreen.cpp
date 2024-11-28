#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mStars = BackgroundStars::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	mStars = nullptr;

	delete mSideBar;
	mSideBar = nullptr;
}

void PlayScreen::StartNewGame() {
	mSideBar->SetHighScore(645987);	//CREATE SAVE SYSTEM
	mSideBar->SetShips(2);

	StartNextLevel();	//Test
}

void PlayScreen::StartNextLevel() {
	mSideBar->SetLevel(116);
}

void PlayScreen::Update() {
	mSideBar->Update();
}

void PlayScreen::Render() {
	mSideBar->Render();
}