#include "GameManager.h"

namespace SDL_Framework {
	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		//main game loop
		while (!mQuit)
		{  
			mTimer->Update();
			//event polling loop, while there are events inside of out events variable
			while (SDL_PollEvent(&mEvents))
			{   // Handle each and every event we want to look for
				switch (mEvents.type)
				{
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}

			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();
			}
		}
	}
	void GameManager::Update() {
		//std::cout << "Delta Time: " << mTimer->DeltaTime() << std::endl;
	}

	void GameManager::LateUpdate() {

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		mTimer = Timer::Instance();

		mParent = new GameEntity(100.0f, 400.0f);
		mChild = new GameEntity(100.0f, 500.0f);

		printf("Child local pos: (%f,%f) \n",
			mChild->Position(GameEntity::Local).x,
			mChild->Position(GameEntity::Local).y);

		mChild->Parent(mParent);

		printf("Child local pos: (%f,%f) \n",
			mChild->Position(GameEntity::Local).x,
			mChild->Position(GameEntity::Local).y);
	}

	GameManager::~GameManager() {
		//Release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		// terminate SDL subsystems
		SDL_Quit();
	}
}

// Notes
// SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255); //Colour red