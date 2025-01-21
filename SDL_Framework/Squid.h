#pragma once
#include "Enemy.h"
#include "Random.h"
#include "Texture.h"

namespace SDL_Framework {

	class Squid : public Enemy {
	public:
		static void CreateDivePaths();

		void Dive(int type = 0) override;
		void Hit(PhysEntity* other) override;

		Squid(int path, int index, bool challenge);
		~Squid();

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		int mCurrentPath;

		bool mWasHit;

		Vector2 LocalFormationPosition() override;

		void HandleDiveState() override;

		void RenderDiveState() override;
	};
}