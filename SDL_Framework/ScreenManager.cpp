#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mBackgroundStars = BackgroundStars::Instance();
	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mOptionScreen = new OptionScreen();
	mCreditScreen = new CreditScreen();
	mHighScoreTable = new HighScoreTable();

	mCurrentScreen = Start;

	
	//mBackground = mAssetManager->GetTexture("invaders.png");
	//mBackground->Position(Vec2_Zero);
	//mBackground->Scale(Vector2(1.5f, 1.5f));

	//SDL_Rect srcRect = { 993, 12, 257, 224 };
	
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	//if (mBackground != nullptr) {
	//	SDL_DestroyTexture(mBackground);
	//	mBackground = nullptr;
	//}

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mOptionScreen;
	mOptionScreen = nullptr;

	delete mCreditScreen;
	mCreditScreen = nullptr;

	delete mHighScoreTable;
	mHighScoreTable = nullptr;
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case ScreenManager::Start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mStartScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mStartScreen->ResetAnimation();
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 3) {
				mCurrentScreen = HighScore;
			}
		}

		break;

	case ScreenManager::Play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver()) {
			mCurrentScreen = Start;
		}
		break;

	case ScreenManager::Option:
		mOptionScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mOptionScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 2) {
				mCurrentScreen = HighScore;
			}
			if (selectedMode == 3) {
				mCurrentScreen = Start;
			}
		}

		break;

	case ScreenManager::Credit:
		mCreditScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mCreditScreen->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = HighScore;
			}
			if (selectedMode == 3) {
				mCurrentScreen = Start;
			}
		}

		break;

	case ScreenManager::HighScore:
		mHighScoreTable->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			int selectedMode = mHighScoreTable->SelectedMode();

			if (selectedMode == 0) {
				mCurrentScreen = Play;
				mPlayScreen->StartNewGame();
			}
			if (selectedMode == 1) {
				mCurrentScreen = Option;
			}
			if (selectedMode == 2) {
				mCurrentScreen = Credit;
			}
			if (selectedMode == 3) {
				mCurrentScreen = Start;
			}
		}

		break;

	default:
		std::cerr << "Unknown state found for game screen" << std::endl;
		break;
	}
}

void ScreenManager::Render() {
	//mBackground = mAssetManager->GetTexture("invaders.png");
	//mAssetManager = AssetManager::Instance();
	//SDL_Rect destRect = { 0, 0, 1400, 1024 };

	//mGraphic->DrawTexture(mBackground, nullptr, &destRect);

	switch (mCurrentScreen) {
		
	case ScreenManager::Start:
		mStartScreen->Render();
		mBackgroundStars->Render();
		break;

	case ScreenManager::Play:
		mPlayScreen->Render();
		//mBackground->Render();
		//mGraphic->Render();

		break;

	case ScreenManager::Option:
		mOptionScreen->Render();
		mBackgroundStars->Render();
		break;

	case ScreenManager::Credit:
		mCreditScreen->Render();
		mBackgroundStars->Render();
		break;

	case ScreenManager::HighScore:
		mHighScoreTable->Render();
		mBackgroundStars->Render();
		break;

	default:
		break;
	}
}