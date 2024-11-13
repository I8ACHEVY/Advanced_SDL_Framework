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

		mInputManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mTex->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
			mTex->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			std::cout << "Space pressed!" << std::endl;
		}
		if (mInputManager->KeyReleased(SDL_SCANCODE_SPACE)) {
			std::cout << "Space released!" << std::endl;
		}

		if (mInputManager->MouseButtonPressed(InputManager::Left)) {
			std::cout << "Left mouse button pressed!" << std::endl;
		}

		if (mInputManager->MouseButtonReleased(InputManager::Left)) {
			std::cout << "Left mouse button released!" << std::endl;
		}

	}

	void GameManager::LateUpdate() {

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mRedShip->Render();
		mTex->Render();

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		mTimer = Timer::Instance();
		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();

		mTex = new Texture("SpriteSheet.png", 182, 54, 22, 22);
		mTex->Scale(Vector2(1.5f, 1.5f));

		mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f,
			Graphics::SCREEN_HEIGHT * 0.5f));

		mRedShip = new Texture("SpriteSheet.png", 182, 78, 20, 20);

		mRedShip->Scale(Vector2(1.5f, 1.5f));
		mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f));

		//mParent = new GameEntity(100.0f, 400.0f);
		//mChild = new GameEntity(100.0f, 500.0f);

		//printf("Child local pos: (%f,%f) \n",
		//	mChild->Position(GameEntity::Local).x,
		//	mChild->Position(GameEntity::Local).y);

		//mChild->Parent(mParent);

		//printf("Child local pos: (%f,%f) \n",
		//	mChild->Position(GameEntity::Local).x,
		//	mChild->Position(GameEntity::Local).y);
	}

	GameManager::~GameManager() {
		//Release pointers/ variables
		delete mTex;
		mTex = nullptr;

		delete mRedShip;
		mRedShip = nullptr;

		//Release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		// terminate SDL subsystems
		SDL_Quit();
	}
}

// Notes
// SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255); //Colour red