#include "Star.h"
#include "PhysicsManager.h"

bool Star::sScroll = false;

Star::Star(int layer) : Texture("Stars.png", 0,0,4,4) {
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	int starColor = mRandom->RandomInt() % 4;

	mSourceRect.x = starColor * 4;

	Position(Vector2((float)(mRandom->RandomInt() % (int)(Graphics::Instance()->SCREEN_WIDTH * 0.75f) + 140.0f),
		(float)(mRandom->RandomInt() % (int)(Graphics::Instance()->SCREEN_HEIGHT * 0.7f) + 270.0f)));

	mFlickerTime = 0.0f;
	mFlickerSpeed = mRandom->RandomRange(0.15f, 1.0f);

	float inverseLayer = 1.0f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = 4.0f / layer;
}

Star::~Star() {
	mTimer = nullptr;
	mRandom = nullptr;
}

void Star::Update() {
	mFlickerTime += mTimer->DeltaTime();

	if (mFlickerTime >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTime = 0.0f;
		mFlickerTime = 0.0f;
	}
}

void Star::Render() {

	if (mVisible) {
		Texture::Render();
	}
}