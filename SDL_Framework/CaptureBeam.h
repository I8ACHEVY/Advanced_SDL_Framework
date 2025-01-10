#pragma once
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"
#include "BoxCollider.h"
//#include "Player.h"

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
	bool IgnoreCollisions();

private:
	float mTotalCaptureTime;
	float mCaptureTimer;
	bool mColliderAdded;
	//bool mIsCaptured;
	//bool mCapturedPlayer;

	BoxCollider* mCollider;

	void RunAnimation() override;

	
};