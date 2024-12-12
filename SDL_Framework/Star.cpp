#include "Star.h"
#include "PhysicsManager.h"

bool Star::sScroll = false;

void Star::Scroll(bool scroll) {
	sScroll = scroll;
}

Star::Star(int layer) : Texture("Stars.png", 0,0,4,4) {
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	int starColor = mRandom->RandomInt() % 4;

	mSourceRect.x = starColor * 4;

	mBounds = Vector2(323.0f, 1065.0f);

	//Boundaries* mBounds = &Graphics::Instance()->GetPlayArea();

	Position(Vector2((float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),	//mBounds->GetWidth()
		(float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));				// mBounds->GetHeight()

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

void Star::ScrollStar() {
	Translate(Vec2_Up * mScrollSpeed);

	Vector2 pos = Position(Local);
	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = (float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
		Position(pos);
	}
}

void Star::Update() {
	mFlickerTime += mTimer->DeltaTime();

	if (mFlickerTime >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTime = 0.0f;
		mFlickerTime = 0.0f;
	}

	if (sScroll) {
		ScrollStar();
	}
}

void Star::Render() {
	if (mVisible) {
		Texture::Render();
	}
}