#pragma once
#include "Texture.h"
#include "Timer.h"


namespace SDL_Framework {
	class AnimatedTexture : public Texture {
	public:
		enum WrapMode { Once = 0, Loop};
		enum AnimDir { Horizontal = 0, Vertical };

		AnimatedTexture(std::string filename, int x, int y, int width, int height,
			int frameCount, float animSpeed, AnimDir animationDir, bool manmaged = true);

		~AnimatedTexture();

		void SetWrapMode(WrapMode mode);

		bool IsAnimating();

		virtual void ResetAnimation();

		void Update();

	protected:
		virtual void RunAnimation();

		Timer* mTimer;
		int mStartx;
		int mStarty;

		int mFrameCount;

		float mAnimationSpeed;
		float mTimePerFrame;
		float mAnimationTimer;

		WrapMode mWrapMode;
		AnimDir mAnimationDirection;

		bool mAnimationDone;
	};
}

