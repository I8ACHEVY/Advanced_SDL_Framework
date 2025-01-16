#pragma once
#include "PhysicsManager.h"
#include "Enemy.h"
#include "CaptureBeam.h"
#include "Player.h"

namespace SDL_Framework {

	class RedShip :
		public Enemy{

	public:

		static void CreateDivePaths();

		void Dive(int type = 0) override;

		void Hit(PhysEntity* other) override;
		bool IgnoreCollision(PhysEntity* Entity);

		RedShip(int path, int index, bool challenge, Player* player);
		~RedShip();

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		static const int MAX_BULLETS = 2;
		Bullet* mBullets[MAX_BULLETS];

		Texture* mRedShip;
		PhysEntity* mCollider;
		CaptureBeam* mCaptureBeam;
		Player* zPlayer;

		bool mVisible;
		bool mEscort;
		int mBossIndex;

		Vector2 LocalFormationPosition() override;

		void HandleDiveState() override;

		void RenderDiveState() override;
	};
}