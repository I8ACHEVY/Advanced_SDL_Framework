#include "CaptureBeam.h"
#include "PhysicsManager.h"

void CaptureBeam::RunAnimation() {
	mCaptureTimer += mTimer->DeltaTime();

	if (mCaptureTimer >= 0.5f && mCaptureTimer <= mTotalCaptureTime - 1.0f) {
		if (!mColliderAdded) {

		AddCollider(new BoxCollider(Vector2(90.0f, 300.0f)), Vector2(0.0f, -40.0f));
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);

		mColliderAdded = true;
		}
	}
	else if (mColliderAdded) {
		
		if (mCaptureTimer >= mTotalCaptureTime) {
			mColliderAdded = false;
		}
	}

	if (mCaptureTimer >= mTotalCaptureTime) {
		mAnimationDone = true;
	}
	else {
		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed) {
			mAnimationTimer -= mAnimationSpeed;
		}

		mSourceRect.x = (int)(mAnimationTimer / mTimePerFrame) * mWidth;

		if (mCaptureTimer < 2.0f) {
			int temp = (int)(mCaptureTimer * 3.5f);
			mSourceRect.h = (int)(temp / 7.0f * mHeight);
		}
		else if (mCaptureTimer > mTotalCaptureTime - 2.0f) {
			int temp = (int)((mTotalCaptureTime - mCaptureTimer) * 3.5f);
			mSourceRect.h = (int)(temp / 7.0f * mHeight);
		}
		else {
			mSourceRect.h = mHeight;
		}
	}
}

void CaptureBeam::Hit(PhysEntity* other) {
	if (IgnoreCollision(other)) {
		return;
	}
	std::cout << "Capture Beam Contact" << std::endl;

	Player* player = dynamic_cast<Player*>(other);
	if (player) {

		Collider* broadPhaseCollider = other->GetBroadPhaseCollider();
		Collider* narrowPhaseCollider = other->GetBroadPhaseCollider();

		if (narrowPhaseCollider) {
			std::cout << "Player is in both" << std::endl;
			mIsCaptured = true;

			if (mIsCaptured) {
				Vector2 beamPosition = AnimatedTexture::Position(World);
				Vector2 beamOrigin = Vector2(beamPosition.x, beamPosition.y - 80.0f);//-160
				Vector2 dir = beamOrigin - player->Position(World);

				float pullSpeed = 100.0f;
				player->Translate(dir.Normalized() * pullSpeed * mTimer->DeltaTime(), World);

				player->Rotate(260.0f * mTimer->DeltaTime());

				std::cout << "Current Player Rotation: " << player->Rotation(World) << std::endl;

				float escapeDistance = 100.0f;
				float distSquared = dir.MagnitudeSqr();

				if (distSquared < escapeDistance * escapeDistance) {
					mIsCaptured = false;
					mZombie = true;
					std::cout << "Zombie Ship" << std::endl;
				}
			}
		}

		if (broadPhaseCollider && broadPhaseCollider->GetType() == Collider::ColliderType::Circle) {
			std::cout << "Player is in circle" << std::endl;

			mOriginalRotation = player->Rotation(World);
			mOriginalPositionY = player->Position(World).y;
			std::cout << "Original rotation and position stored" << std::endl;

			mIsCaptured = false;
		}

		if (!broadPhaseCollider || (broadPhaseCollider->GetType() !=
			Collider::ColliderType::Box && broadPhaseCollider->GetType() !=
			Collider::ColliderType::Circle)) {

			std::cout << "Player is in circle" << std::endl;

			if (mIsCaptured) {
				std::cout << "Player Escaping: Resetting Rotation" << std::endl;
				float pullSpeed = 150.0f;

				player->Rotate(mOriginalRotation);

				Vector2 currentPos = player->Position(World);

				Vector2 returnDir = Vector2(currentPos.x - mOriginalPositionY);//Graphics::SCREEN_HEIGHT * 0.8f)
				player->Translate(returnDir.Normalized() * pullSpeed * mTimer->DeltaTime(), World);
			}
		}
	}
}

bool CaptureBeam::IsCaptured() const {
	return mIsCaptured;
}

bool CaptureBeam::Zombie() const {
	return mZombie;
}

bool CaptureBeam::IgnoreCollision(PhysEntity* entity) {
	if (auto* player = dynamic_cast<Player*>(entity)) {

		if (mCaptureTimer <= 2.1f || mCaptureTimer >= mTotalCaptureTime - 2.0) {
			return false;
		}
		else {
			return true;
		}
	}
	return true;
}

CaptureBeam::CaptureBeam()
	: AnimatedTexture("CaptureBeam.png", 0, 0, 184, 320, 3, 0.5f, Horizontal), 
	mCollider(nullptr),
	mZombie(false){

	mTotalCaptureTime = 6.0f;
	ResetAnimation();
	mTag = "Capture";
	std::cout << "CaptureBeam Tag set to" << mTag << std::endl;

	//AddCollider(new BoxCollider(Vector2(160.0f, 60.0f)), Vector2(0.0f, -140.0f));
	//mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);
}


CaptureBeam::~CaptureBeam() {
	if (mCollider) {
		delete mCollider;
		mCollider = nullptr;
	}
}

void CaptureBeam::ResetAnimation() {
	AnimatedTexture::ResetAnimation();
	mCaptureTimer = 0.0f;
	mSourceRect.h = 0;
}

void CaptureBeam::Render() {
	Vector2 pos = AnimatedTexture::Position(World);
	Vector2 worldScale = AnimatedTexture::Scale(World);
	Vector2 scale(worldScale.x * 0.7f, worldScale.y * 0.7f);

	mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
	mDestinationRect.w = (int)(mWidth * scale.x);
	mDestinationRect.h = mSourceRect.h;

	mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, AnimatedTexture::Rotation(World));

	PhysEntity::Render();
}