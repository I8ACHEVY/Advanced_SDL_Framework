#include "GameManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"// remove after tests

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
		mRedShip->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_MINUS)) {
			int currentMusicVolume = Mix_VolumeMusic(-1);
			int newMusicVolume = currentMusicVolume - 10;
			if (newMusicVolume < 0) newMusicVolume = 0;

			mAudioManager->MusicVolume(newMusicVolume);

			int currentSFXVolume = Mix_Volume(-1, -1);
			int newSFXVolume = currentMusicVolume - 10;
			if (newSFXVolume < 0) newSFXVolume = 0;

			mAudioManager->SFXVolume(newSFXVolume);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_EQUALS)) {
			int currentMusicVolume = Mix_VolumeMusic(-1); 
			int newMusicVolume = currentMusicVolume + 10;  
			if (newMusicVolume > MIX_MAX_VOLUME) newMusicVolume = MIX_MAX_VOLUME; 

			mAudioManager->MusicVolume(newMusicVolume); 

			int currentSFXVolume = Mix_Volume(-1, -1); 
			int newSFXVolume = currentSFXVolume + 10;   
			if (newSFXVolume > MIX_MAX_VOLUME) newSFXVolume = MIX_MAX_VOLUME;    

			mAudioManager->SFXVolume(newSFXVolume);
		}

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


		mPhys1->Position(mTex->Position() + Vector2(-7,-7));
		mPhys1->Scale(mTex->Scale());
		mPhys1->Rotate(mTex->Rotation());

		mPhys2->Position(mTex->Position() + Vector2(2, -90));
		mPhys2->Scale(mTex->Scale());
		mPhys2->Rotate(mTex->Rotation());

		mPhys3->Position(mRedShip->Position() + Vector2(-6,-6));
		mPhys3->Scale(mRedShip->Scale());
		mPhys3->Rotate(mRedShip->Rotation());

		mPhys4->Position(mRedShip->Position() + Vector2(3, -90));
		mPhys4->Scale(mRedShip->Scale());
		mPhys4->Rotate(mRedShip->Rotation());

	}

	void GameManager::LateUpdate() {
		mInputManager->UpdatePrevInput();
		mPhysicsManager->Update();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mRedShip->Render();
		mTex->Render();
		mPhys1->Render();
		mPhys2->Render();
		mPhys3->Render();
		mPhys4->Render();

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
		mAudioManager = AudioManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);


		mTex = new Texture("SpriteSheet.png", 182, 54, 22, 22);
		mTex->Scale(Vector2(1.5f, 1.5f));
		mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f,Graphics::SCREEN_HEIGHT * 0.5f));

		mPhys1 = new PhysEntity();
		mPhys1->AddCollider(new BoxCollider(Vector2(23.0f, 23.0f)));
		mPhys1->mId = mPhysicsManager->RegisterEntity(mPhys1, PhysicsManager::CollisionLayers::Friendly); // testing

		mPhys2 = new PhysEntity();
		mPhys2->AddCollider(new BoxCollider(Vector2(5.0f, 5.0f)));
		mPhys2->mId = mPhysicsManager->RegisterEntity(mPhys2, PhysicsManager::CollisionLayers::FriendlyProjectile); // testing

		//mTexCollision = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.6f,
		//	AnimatedTexture::Horizontal);
		//mTexCollision->Scale(Vector2(1.5f, 1.5f));
		//mTexCollision->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f,
		//	Graphics::SCREEN_HEIGHT * 0.5f));


		mRedShip = new Texture("SpriteSheet.png", 182, 78, 20, 20);
		mRedShip->Scale(Vector2(1.5f, 1.5f));
		mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f));

		mPhys3 = new PhysEntity();
		mPhys3->AddCollider(new BoxCollider(Vector2(23.0f, 23.0f)));
		mPhys3->mId = mPhysicsManager->RegisterEntity(mPhys3, PhysicsManager::CollisionLayers::Hostile); // testing

		mPhys4 = new PhysEntity();
		mPhys4->AddCollider(new BoxCollider(Vector2(5.0f, 5.0f)));
		mPhys4->mId = mPhysicsManager->RegisterEntity(mPhys4, PhysicsManager::CollisionLayers::HostileProjectile); // testing	

		//mRedShipCollision = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.6f,
		//	AnimatedTexture::Horizontal);
		//mRedShipCollision->Scale(Vector2(1.5f, 1.5f));
		//mRedShipCollision->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f,
		//	Graphics::SCREEN_HEIGHT * 0.5f));


		mFontTex = new Texture("GALAGA", "ARCADE.TTF", 72, { 255, 10, 10 });
		mFontTex->Position(Vector2(300, 50));
	}

	GameManager::~GameManager() {
		//Release pointers/ variables
		delete mTex;
		mTex = nullptr;

		delete mRedShip;
		mRedShip = nullptr;

		delete mFontTex;
		mFontTex = nullptr;

		delete mPhys1;
		mPhys1 = nullptr;

		delete mPhys2;
		mPhys2 = nullptr;

		delete mPhys3;
		mPhys3 = nullptr;

		delete mPhys4;
		mPhys4 = nullptr;

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

		// terminate SDL subsystems
		SDL_Quit();
	}
}

// Notes
// SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255); //Colour red