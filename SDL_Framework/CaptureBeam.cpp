#include "CaptureBeam.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void CaptureBeam::RunAnimation() {
	mCaptureTimer += mTimer->DeltaTime();

	if (mCaptureTimer >= mTotalCaptureTime) {
		mAnimationDone = true;
		
		if (mCapturedPlayer) {
			mCapturedPlayer->StartRotation();
		}
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
		else if (mCaptureTimer > mTotalCaptureTime - 2.0f) {		// possible hard set > 4)
			int temp = (int)((mTotalCaptureTime - mCaptureTimer) * 3.5f);
			mSourceRect.h = (int)(temp / 7.0f * mHeight);
		}
		else {
			mSourceRect.h = mHeight;
		}
	}
}

void CaptureBeam::Hit(PhysEntity* other) {
	if (IgnoreCollision()) return;
	std::cout << "Capture Beam Contact" << std::endl;
}

void CaptureBeam::SetCapturedShip(Player* player) {
	mCapturedPlayer = player;
}

bool CaptureBeam::IgnoreCollisions() {
	return mCaptureTimer <= 2.1f || mCaptureTimer >= mTotalCaptureTime - 2.0;
}

CaptureBeam::CaptureBeam()
	: AnimatedTexture("CaptureBeam.png", 0, 0, 184, 320, 3, 0.5f, Horizontal) {
	mTotalCaptureTime = 6.0f;
	ResetAnimation();

	AddCollider(new BoxCollider(Vector2(160.0f, 60.0f)), Vector2(0.0f, -140.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);
}


CaptureBeam::~CaptureBeam() {
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