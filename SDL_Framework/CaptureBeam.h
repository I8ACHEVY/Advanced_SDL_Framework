#pragma once
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"
#include "Player.h"

using namespace SDL_Framework;

class CaptureBeam :
	public AnimatedTexture,
	public PhysEntity
{
public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;

	void Hit(PhysEntity* other) override;
	bool IgnoreCollision();

private:
	float mTotalCaptureTime;
	float mCaptureTimer;
	bool mColliderAdded;
	bool mIsCaptured;

	PhysEntity* mCollider;

	void RunAnimation() override;
};