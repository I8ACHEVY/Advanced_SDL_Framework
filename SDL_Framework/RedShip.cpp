#include "RedShip.h"
#include "BoxCollider.h"
#include "AudioManager.h"

void RedShip::Hit(PhysEntity* other) {
	if (IgnoreCollision()) {
		return;
	}
}

//bool RedShip::IgnoreCollision(PhysEntity* Entity) {
//	if (auto* player = dynamic_cast<Player*>(entity)) {
//
//		if (mCaptureTimer <= 2.1f || mCaptureTimer >= mTotalCaptureTime - 2.0) {
//			return false;
//		}
//		else {
//			return true;
//		}
//	}
//	return true;
//}

RedShip::RedShip() {
	//'Texture("PlayerShips.png", 60, 0, 60, 64), mCollider(nullptr) {

	mTag = "RedShip";

	mRedShip = new Texture("PlayerShips.png", 60, 0, 60, 64);
	mRedShip->Parent(this);
	mRedShip->Position(Vec2_Zero);
	mRedShip->Scale(Vector2(0.7f, 0.7f));

	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f,
		AnimatedTexture::Horizontal);

	mDeathAnimation->Parent();
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	AddCollider(new BoxCollider(Vector2(10.0f, 45.0f)));
	AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(12.0f, 5.0f));
	AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(-12.0f, 5.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this,
		PhysicsManager::CollisionLayers::Hostile);
}

RedShip::~RedShip() {
	if (mCollider) {
		delete mCollider;
		mCollider = nullptr;
	}

	if (mDeathAnimation) {
		delete mDeathAnimation;
		mDeathAnimation = nullptr;
	}
}

void RedShip::Render() {

	Vector2 pos = Position(World);
	//Vector2 worldScale = Scale(World);
	//Vector2 scale(worldScale.x * 0.7f, worldScale.y * 0.7f);

	//mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	//mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
	//mDestinationRect.w = (int)(mWidth * scale.x);
	//mDestinationRect.h = mSourceRect.h;

	//mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Texture::Rotation(World));

	PhysEntity::Render();

	//Vector2 pos = Position(World);
	Vector2 scale = Scale(World);

	mRedShip->Render();

	//PhysEntity::Render();
}
