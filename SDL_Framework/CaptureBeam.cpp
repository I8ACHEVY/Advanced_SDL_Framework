#include "CaptureBeam.h"
#include "PhysicsManager.h"

void CaptureBeam::RunAnimation() {
	mCaptureTimer += mTimer->DeltaTime();

	if (mCaptureTimer >= 2.1f && mCaptureTimer <= mTotalCaptureTime - 2.0f) {
		if (!mColliderAdded) {

		AddCollider(new BoxCollider(Vector2(140.0f, 190.0f)), Vector2(0.0f, -30.0f));
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
	if (IgnoreCollision()) {
		return;
	}
	std::cout << "Capture Beam Contact" << std::endl;

	 Player* player = dynamic_cast<Player*>(other);
	 if (player) {

		 Vector2 beamPosition = AnimatedTexture::Position(World);
		 float beamWidth = mWidth * AnimatedTexture::Scale(World).x * 0.7f;
		 float beamHeight = mHeight * AnimatedTexture::Scale(World).y * 0.7f;
		 Vector2 beamOrigin = Vector2(beamPosition.x, beamPosition.y - beamHeight * 0.5f);

		 Vector2 dir = beamOrigin - player->Position(World);

		 float pullSpeed = 100.0f;
		 player->Position(player->Position(World) + dir * pullSpeed * mTimer->DeltaTime());

		 player->Rotate(260.0f * mTimer->DeltaTime());

		 //if (player->Position(World) < beamOrigin) {
			// player->Rotate(0.0f * mTimer->DeltaTime());
			// mIsCaptured = true;
		 //}
	 }

}

bool CaptureBeam::IgnoreCollision() {
	return mCaptureTimer <= 2.1f || mCaptureTimer >= mTotalCaptureTime - 2.0;
}

CaptureBeam::CaptureBeam()
	: AnimatedTexture("CaptureBeam.png", 0, 0, 184, 320, 3, 0.5f, Horizontal), mCollider(nullptr) {
	mTotalCaptureTime = 6.0f;
	ResetAnimation();
	mTag = "CaptureBeam";

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