#pragma once
#include "AnimatedTexture.h"

using namespace SDL_Framework;

class CaptureBeam :
	public AnimatedTexture
{
public:
	CaptureBeam();
	~CaptureBeam();

	void ResetAnimation() override;
	void Render() override;

private:
	float mTotalCaptureTime;
	float mCaptureTimer;

	void RunAnimation() override;
};