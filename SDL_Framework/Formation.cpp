#include "Formation.h"

Formation::Formation() {
	mTimer = Timer::Instance();

	mOffsetAmount = 10.0f;
	mOffsetDelay = 0.4f;
	mOffsetTimer = 0.0f;
	mOffsetDirection = 1;
	mOffsetCounter = 4;

	mPulseTimer = 0.0f;
	mPulseDelay = 0.6f;
	mPulseCounter = 0;
	mPulseDirection = 1;

	mLocked = false;

	mGridSize = Vector2(23.0f, 40.0f); // formation spacing
}


Formation::~Formation() {
	mTimer = nullptr;
}

void Formation::Update() {
	if (!mLocked || mOffsetCounter != 4) {
		mOffsetTimer += mTimer->DeltaTime();

		if (mOffsetTimer >= mOffsetDelay) {
			mOffsetCounter++;

			Translate(Vec2_Right * (float)mOffsetDirection *
			mOffsetAmount, World);

			if (mOffsetCounter == 8) {
				mOffsetCounter = 0;
				mOffsetDirection *= -1;
			}

			mOffsetTimer = 0.0f;
		}
	}
	else {
		mPulseTimer += mTimer->DeltaTime();

		if (mPulseTimer >= mPulseDelay) {
			mPulseCounter += mPulseDirection;

			mGridSize.x += (mPulseDirection * ((mPulseCounter % 2) ? 1 : 2));

			if (mPulseCounter == 4 || mPulseCounter == 0) {
				mPulseDirection *= -1;
			}

			mPulseTimer = 0.0f;
		}
	}
}

int Formation::GetTick() {
	if (!mLocked || mOffsetCounter != 4) {
		return mOffsetCounter;
	}
	else {
		return mPulseCounter;
	}
}

Vector2 Formation::GridSize() {
	return mGridSize;
}

bool Formation::Locked() {
	return mLocked && mOffsetCounter == 4;
}

void Formation::Lock() {
	mLocked = true;
}
