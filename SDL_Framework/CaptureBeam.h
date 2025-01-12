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
	bool IsCaptured() const;


private:
	float mTotalCaptureTime;
	float mCaptureTimer;
	float mOriginalRotation;

	Vector2 mOriginalPosition;
	Vector2 mBeamOrigin;

	bool mColliderAdded;
	bool mIsCaptured;
	
	std::string mTag;

	PhysEntity* mCollider;

	void RunAnimation() override;
};