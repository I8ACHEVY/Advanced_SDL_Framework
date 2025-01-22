#pragma once

#include "GLTexture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDL_Framework;

class Star : public GLTexture {
public:
	Star(int layer);
	~Star();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	Random* mRandom;
	Vector2 mBounds;

	static bool sScroll;
	float mScrollSpeed;
	
	bool mVisible;
	float mFlickerTime;
	float mFlickerSpeed;
};