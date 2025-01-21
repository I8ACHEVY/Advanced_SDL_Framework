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
}

void ScreenManager::Update() {
	mBackgroundStars->Update();

	switch (mCurrentScreen) {
	case ScreenManager::Start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			
			mCurrentScreen = Play;
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();
		}

		break;

	case ScreenManager::Play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver()) {
			mCurrentScreen = Start;
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

	default:
		break;
	}
}