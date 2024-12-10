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

		mInputManager->Update();
		mScreenManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_MINUS)) {
			mAudioManager->DecreaseVolume();

		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_EQUALS)) {
			mAudioManager->IncreaseVolume(); 

		}

		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			//mTex->Rotate(-260.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			//mTex->Rotate(260.0f * mTimer->DeltaTime());
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
				//mTex->Scale(Vector2(scaleFactor, scaleFactor));
			}
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			float scaleFactor = 1.5f + mScaleTimeC * 0.3f;
			//mTex->Scale(Vector2(scaleFactor, scaleFactor));
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

		if (mInputManager->KeyDown(SDL_SCANCODE_I) || mInputManager->KeyDown(SDL_SCANCODE_KP_8)) {
			//mRedShip->Translate(Vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_K) || mInputManager->KeyDown(SDL_SCANCODE_KP_2)) {
			//mRedShip->Translate(Vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_J) || mInputManager->KeyDown(SDL_SCANCODE_KP_4)) {
			//mRedShip->Translate(Vector2(-40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_L) || mInputManager->KeyDown(SDL_SCANCODE_KP_6)) {
			//mRedShip->Translate(Vector2(40.0F, 0) * mTimer->DeltaTime(), GameEntity::World);
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_U)) {
			//mRedShip->Rotate(-260.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_O)) {
			//mRedShip->Rotate(260.0f * mTimer->DeltaTime());
		}

		if (mInputManager->MouseButtonPressed(InputManager::Left)) {
			std::cout << "Left mouse button pressed!" << std::endl;
			mAudioManager->PlaySFX("coin_credit.wav", 0, -1);			//audio test
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
				//mRedShip->Scale(Vector2(scaleFactor, scaleFactor));
			}
		}

		if (mInputManager->KeyDown(SDL_SCANCODE_PERIOD)) {
			float scaleFactor = 1.5f + mScaleTimePER * 0.3f;
			//mRedShip->Scale(Vector2(scaleFactor, scaleFactor));
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_M)) {
			mScaleTimeM = 0.0f;
		}

		if (mInputManager->KeyReleased(SDL_SCANCODE_PERIOD)) {
			mScaleTimePER = 0.0f;
		}
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mScreenManager->Render();

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
		mAudioManager = AudioManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();
		mRandom = Random::Instance();
		mScreenManager = ScreenManager::Instance();

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile);
		
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);
		
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);
		
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);

	}

	GameManager::~GameManager() {
		//Release pointers/ variables

		//Release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		Random::Release();
		mRandom = nullptr;

		ScreenManager::Release();
		mScreenManager = nullptr;

		// terminate SDL subsystems
		SDL_Quit();
	}
}

// Notes
// SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255); //Colour red