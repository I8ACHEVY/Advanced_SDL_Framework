#include "Player.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {

	//if (mInput->KeyDown(SDL_SCANCODE_W) || mInput->KeyDown(SDL_SCANCODE_UP)) {
	//	Translate(Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
	//}
	//else if (mInput->KeyDown(SDL_SCANCODE_S) || mInput->KeyDown(SDL_SCANCODE_DOWN)) {
	//	Translate(-Vec2_Up * mMoveSpeed * mTimer->DeltaTime(), World);
	//}

	if (mInput->KeyDown(SDL_SCANCODE_A) || mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_D) || mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}

	Vector2 pos = Position(Local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) || mInput->MouseButtonPressed(InputManager::Left)) {
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (!mBullets[i]->Active()) {
				mBullets[i]->Fire(Position());
				mAudio->PlaySFX("Fire.wav");
				break;
			}
		}
	}
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(323.0f, 1065.0f);

	mShip = new Texture("PlayerShips.png", 0, 0, 60, 64);
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);
	mShip->Scale(Vector2(0.7f, 0.7f));


	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f,
		AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	AddCollider(new BoxCollider(Vector2(10.0f, 45.0f)));
	AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(12.0f, 5.0f));
	AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(-12.0f, 5.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this,
		PhysicsManager::CollisionLayers::Friendly);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (auto bullet : mBullets) {
		delete bullet;
		bullet = nullptr;
	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::WasHit() {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("PlayerExplosion.wav",0, -1);
}

bool Player::IgnoreCollision() {
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mWasHit = true;

}

void Player::Update() {
	if (mAnimating){
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();
		}

		PhysEntity::Render();
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i]->Render();
	}
}