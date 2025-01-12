#include "Player.h"
#include "PhysicsManager.h"


void Player::HandleMovement() {

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

//void Player::HandleCaptureMovement() {
//	Vector2 beamPosition;
//	Vector2 dir = beamPosition - Position();
//	float distance = dir.Magnitude();
//	float pullSpeed = 100.0f;
//	Vector2 pullVector = dir.Normalized() * pullSpeed * mTimer->DeltaTime();
//	Position(Position() + pullVector);
//
//	//mAnimating = false;
//	//mWasHit = false;
//}

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
	mIsCaptured = false;

	mScore = 0;
	mLives = 20;

	mMoveSpeed = 250.0f;
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

void Player::SetVisible(bool visible) {
	mVisible = visible;
}

bool Player::IsVisible() {
	return mVisible;
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

bool Player::WasHit() {
	return mWasHit;
}

bool Player::IsCaptured() const{
	return mIsCaptured;
}

bool Player::IgnoreCollision() {
	return !mVisible || mAnimating || !Active();
}

void Player::Hit(PhysEntity* other) {

	std::cout << "Player Hit by Tag" << other->GetTag() << std::endl;
	if (other->GetTag() == "Capture") {
		mAnimating = false;
		mWasHit = false;
		
		//if (!mIsCaptured) {
		//	mOriginalPosition = Position(World);
		//	mOriginalRotation = Rotation();
		//}
		mIsCaptured = true;
	}
	else if (other->GetTag() == "Butterfly" || other->GetTag() == "Wasp" || other->GetTag() == "Boss") {
		if (!mIsCaptured) {
			mLives -= 1;
			mAnimating = true;
			mDeathAnimation->ResetAnimation();
			mAudio->PlaySFX("PlayerExplosion.wav", 0, -1);
			mWasHit = true;
		}
	}

}

void Player::Update() {
	if (mAnimating && !mIsCaptured){
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();

		if (mWasHit) {
			mWasHit = false;
		}
	}
	else {
		if (Active()) {
			if (mIsCaptured) {

				//Vector2 beamOrigin = Vector2(0.0f, 0.0f);
				//Vector2 dir = beamOrigin - Position(World);
				//float pullSpeed = 100.0f;
				//Position(Position(World) + dir.Normalized() * pullSpeed * mTimer->DeltaTime());
				//float angleToBeam = atan2(beamOrigin.y - Position(World).y, beamOrigin.x - Position(World).x);
				//Rotate(angleToBeam);

				//float distSquared = dir.x * dir.x + dir.y * dir.y;
				//if (distSquared < 100.0f * 100.0f) {
				//	mIsCaptured = false;
				//}

				HandleFiring();
			}
			else {
				if (!mIsCaptured) {
					HandleMovement();
					HandleFiring();
				}
			}
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