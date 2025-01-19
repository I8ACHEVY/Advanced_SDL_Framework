#pragma once

#include "Texture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDL_Framework;

class Star : public Texture {
public:
	static void Scroll(bool scroll);

	static void Visible(bool Visible);

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

	void ScrollStar();
};