#include "CaptureBeam.h"
#include "PhysicsManager.h"

void CaptureBeam::RunAnimation() {
	mCaptureTimer += mTimer->DeltaTime();

	if (mCaptureTimer >= 2.1f && mCaptureTimer <= mTotalCaptureTime - 2.0f) {
		if (!mColliderAdded) {

		AddCollider(new BoxCollider(Vector2(20.0f, 20.0f)), Vector2(0.0f, 170.0f));
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

		 if (!mIsCaptured) {
			 //Vector2 newPosition = Vector2(player->Position(World).x, Graphics::SCREEN_HEIGHT * 0.8f);
			 std::cout << "original rot and pos stored" << std::endl;
			 mIsCaptured = true;
		 }

		 if (mIsCaptured) {
			 Vector2 beamPosition = AnimatedTexture::Position(World);
			 Vector2 beamOrigin = Vector2(beamPosition.x, beamPosition.y - 160.0f);
			 Vector2 dir = beamOrigin - player->Position(World);

			 //float beamWidth = mWidth * AnimatedTexture::Scale(World).x * 0.7f;
			 //float beamHeight = mHeight * AnimatedTexture::Scale(World).y * 0.7f;

			 //float minDistSquared = std::numeric_limits<float>::max();

			 float pullSpeed = 150.0f;
			 player->Translate(dir.Normalized() * pullSpeed * mTimer->DeltaTime(), World);

			 player->Rotate(260.0f * mTimer->DeltaTime());

			 std::cout << "Current Player Rotation: " << player->Rotation(World) << std::endl;

			 float escapeDistance = 160.0f; //beamWidth;
			 float distSquared = dir.MagnitudeSqr();

			 if (distSquared > escapeDistance * escapeDistance) {
				 //minDistSquared = distSquared;
				 std::cout << "Player Escaping: Resetting Rotation" << std::endl;
				 mIsCaptured = false;

				 //Vector2 currentPosition = player->Position(World);

				 //float homePositionX = currentPosition.x;
				 //float homePositionY = Graphics::SCREEN_HEIGHT * 0.8f;
				 // 
				 //if (currentPosition.y > homePositionY) {
					Vector2 returnDir = Vector2(player->Position(World).y - Graphics::SCREEN_HEIGHT * 0.8f);
					player->Translate(returnDir.Normalized() * pullSpeed * mTimer->DeltaTime(), World);
					player->Rotate(90.0f);
				 //}
				 //else {
					// //player->SetPosition(Vector2(homePositionX, homePositionY), World);
				 //}
			 }
		 }
		 //else {
			// player->Rotation(mOriginalRotation);
			// player->Position(mOriginalPosition);
		 //}

	}
}

bool CaptureBeam::IsCaptured() const {
	return mIsCaptured;
}

bool CaptureBeam::IgnoreCollision(PhysEntity* entity) {
	if (auto* player = dynamic_cast<Player*>(entity)) {

		if (mCaptureTimer <= 2.1f || mCaptureTimer >= mTotalCaptureTime - 2.0) {	//add if and else from just a return 4
			return false;
		}
		else {
			return true;
		}
	}
	return true;
}

CaptureBeam::CaptureBeam()
	: AnimatedTexture("CaptureBeam.png", 0, 0, 184, 320, 3, 0.5f, Horizontal), mCollider(nullptr) {
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