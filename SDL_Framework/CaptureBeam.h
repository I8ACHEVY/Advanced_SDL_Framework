#pragma once
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"
#include "Player.h"

using namespace SDL_Framework;

class CaptureBeam :
	public AnimatedTexture,
	public PhysEntity {

public:
	enum class Type {
		Enemy,
		CaptureBeam
	};

	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;

	void Hit(PhysEntity* other) override;
	bool IgnoreCollision(PhysEntity* Entity);

private:
	float mTotalCaptureTime;
	float mCaptureTimer;
	float mOriginalRotation;
	float mCapturedCoolDownTimer;

	Vector2 mOriginalPositionY;
	Vector2 mBeamOrigin;

	bool mColliderAdded;
	bool mIsCapturedCoolDown;

	std::string mTag;

	PhysEntity* mCollider;
	Player* mIsCapturing;
	Player* mZombie;
	Player* mCaptureRange;

	void RunAnimation() override;
	bool IsCapturedCoolDown(bool value);
};