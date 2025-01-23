#pragma once
#include "Enemy.h"
#include "Random.h"
#include "GLTexture.h"

namespace SDL_Framework {

	class Squid : public Enemy {
	public:

		void Hit(PhysEntity* other) override;

		Squid(int index, bool challenge);
		~Squid();

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		int mCurrentPath;

		bool mWasHit;

		Vector2 LocalFormationPosition() override;

	};
}