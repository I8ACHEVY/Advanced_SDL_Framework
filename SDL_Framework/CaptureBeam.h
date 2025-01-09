#pragma once
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"

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

	void RunAnimation() override;
};