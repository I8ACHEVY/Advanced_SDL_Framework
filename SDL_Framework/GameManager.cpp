#include "GameManager.h"
#include "Level.h"

namespace SDL_Framework {
	GameManager* GameManager::sInstance = nullptr;
	GLTexture* mBorderTexture = nullptr;

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
		
		while (!mQuit)
		{  
			mTimer->Update();
			
			while (SDL_PollEvent(&mEvents))
			{   
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

		if (mInputManager->KeyDown(SDL_SCANCODE_M)) {
			if (mAudioManager->Muted()) {
				mAudioManager->Unmute();
			}
			else {
				mAudioManager->Mute();
			}
		}
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mScreenManager->Render();

		if (mBorderTexture) {
		
			mBorderTexture->Render(); //(0, 0, 1070, 1040);
			mBorderTexture->Position(530,520);
			mBorderTexture->Scale(Vector2(1.35f, 1.35f));
		}

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false){//, mBorderTexture(nullptr) {
		Graphics::SetMode(Graphics::RenderMode::GL);
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

		mBorderTexture = new GLTexture("Border.png");
		
		if (!mBorderTexture) {
			std::cerr << "Failed to load border texture: " << IMG_GetError() << std::endl;
		}

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

		if (mBorderTexture != nullptr) {
			delete mBorderTexture;
			mBorderTexture = nullptr;
		}

		// terminate SDL subsystems
		SDL_Quit();
	}
}
