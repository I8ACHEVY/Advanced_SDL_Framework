#pragma once
#include "AnimatedTexture.h"
#include "GLTexture.h"

namespace SDL_Framework {

	class GLAnimatedTexture
		: public GLTexture {

	protected:
		Timer* mTimer;

		Animation mAnim;

		virtual void RunAnimation();

	public:
		GLAnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts animationDir, bool managed = false);
		~GLAnimatedTexture();

		void SetWrapMode(Animation::WrapModes mode);

		virtual void ResetAnimation();
		bool IsAnimating();

		void Update();
	};
}