#include "GLAnimatedTexture.h"

namespace SDL_Framework {

	void GLAnimatedTexture::RunAnimation() {
		if (!mAnim.done) {
			mAnim.frameTimer += mTimer->DeltaTime();

			if (mAnim.frameTimer >= mAnim.speed) {
				if (mAnim.wrapMode == Animation::WrapModes::Loop) {
					// reset timer, accounting for extra time
					mAnim.frameTimer -= mAnim.speed;
				}
				else {
					mAnim.done = true;
					// back up the timer to the last frame
					mAnim.frameTimer = mAnim.speed - mAnim.timePerFrame;
				}
			}

			if (mAnim.layout == Animation::Layouts::Horizontal) {
				mSourceRect.x = mAnim.startX + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mWidth;
			}
			else {
				mSourceRect.y = mAnim.startY + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mHeight;
			}
		}
	}

	GLAnimatedTexture::GLAnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts layout, bool managed)
		: GLTexture(filename, x, y, w, h, managed) {
		mTimer = Timer::Instance();

		mAnim.startX = x;
		mAnim.startY = y;

		mAnim.frameCount = frameCount;
		mAnim.speed = animationSpeed;
		mAnim.timePerFrame = mAnim.speed / mAnim.frameCount;
		mAnim.frameTimer = 0.0f;

		mAnim.wrapMode = Animation::WrapModes::Loop;
		mAnim.layout = layout;

		mAnim.done = false;
	}

	GLAnimatedTexture::~GLAnimatedTexture() {}

	void GLAnimatedTexture::SetWrapMode(Animation::WrapModes wrapMode) {
		mAnim.wrapMode = wrapMode;
	}

	void GLAnimatedTexture::ResetAnimation() {
		mAnim.frameTimer = 0.0f;
		mAnim.done = false;
	}

	bool GLAnimatedTexture::IsAnimating() {
		return !mAnim.done;
	}

	void GLAnimatedTexture::Update() {
		RunAnimation();
	}
}