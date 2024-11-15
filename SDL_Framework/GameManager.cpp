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

		mTex->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W) || mInputManager->KeyDown(SDL_SCANCODE_UP)) {
			mTex->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S) || mInputManager->KeyDown(SDL_SCANCODE_DOWN)) {
			mTex->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_A) || mInputManager->KeyDown(SDL_SCANCODE_LEFT)) {
			mTex->Translate(Vector2(-40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D) || mInputManager->KeyDown(SDL_SCANCODE_RIGHT)) {
			mTex->Translate(Vector2(40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			mTex->Rotate(-260.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			mTex->Rotate(260.0f * mTimer->DeltaTime());
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
			mScaleTimeZ += mTimer->DeltaTime();
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			mScaleTimeC += mTimer->DeltaTime();
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
			float scaleFactor = 1.5f - mScaleTimeZ * 0.3f;
			if (scaleFactor > 0.1f) {
				mTex->Scale(Vector2(scaleFactor, scaleFactor));
			}
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			float scaleFactor = 1.5f + mScaleTimeC * 0.3f;
			mTex->Scale(Vector2(scaleFactor, scaleFactor));
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_Z)) {
			mScaleTimeZ = 0.0f;
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_C)) {
			mScaleTimeC = 0.0f;
		}

		//SECOND SET OF MOVEMENT FOR SECOND TEXTURE (IJKL and KeyPad Numbers 8,6,2,4)
		//SECOND SET OF ROTATION (U LEFT, O RIGHT)
		//SECOND SET OF SCALING (M DOWN, . UP)
		mRedShip->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_I) || mInputManager->KeyDown(SDL_SCANCODE_KP_8)) {
			mRedShip->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_K) || mInputManager->KeyDown(SDL_SCANCODE_KP_2)) {
			mRedShip->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_J) || mInputManager->KeyDown(SDL_SCANCODE_KP_4)) {
			mRedShip->Translate(Vector2(-40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_L) || mInputManager->KeyDown(SDL_SCANCODE_KP_6)) {
			mRedShip->Translate(Vector2(40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_U)) {
			mRedShip->Rotate(-260.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_O)) {
			mRedShip->Rotate(260.0f * mTimer->DeltaTime());
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

		if (mInputManager->KeyDown(SDL_SCANCODE_M)) {
			mScaleTimeM += mTimer->DeltaTime();
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_PERIOD)) {
			mScaleTimePER += mTimer->DeltaTime();
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_M)) {
			float scaleFactor = 1.5f - mScaleTimeM * 0.3f;
			if (scaleFactor > 0.1f) {
				mRedShip->Scale(Vector2(scaleFactor, scaleFactor));
			}
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_PERIOD)) {
			float scaleFactor = 1.5f + mScaleTimePER * 0.3f;
			mRedShip->Scale(Vector2(scaleFactor, scaleFactor));
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_M)) {
			mScaleTimeM = 0.0f;
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_PERIOD)) {
			mScaleTimePER = 0.0f;
		}
	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mRedShip->Render();
		mTex->Render();

		mFontTex->Render();

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

		//mTex = new Texture("SpriteSheet.png", 182, 54, 22, 22);
		//mTex->Scale(Vector2(1.5f, 1.5f));
		//mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f,
		//	Graphics::SCREEN_HEIGHT * 0.5f));

		mTex = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.6f,
			AnimatedTexture::Horizontal);
		mTex->Scale(Vector2(1.5f, 1.5f));
		mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f,
			Graphics::SCREEN_HEIGHT * 0.5f));

		//mRedShip = new Texture("SpriteSheet.png", 182, 78, 20, 20);
		//mRedShip->Scale(Vector2(1.5f, 1.5f));
		//mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f));

		mRedShip = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.6f,
			AnimatedTexture::Horizontal);
		mRedShip->Scale(Vector2(1.5f, 1.5f));
		mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f,
			Graphics::SCREEN_HEIGHT * 0.5f));


		mFontTex = new Texture("GALAGA", "ARCADE.TTF", 72, { 255, 10, 10 });
		mFontTex->Position(Vector2(400, 200));

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


		delete mFontTex;
		mFontTex = nullptr;

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