#pragma once
#include "AnimatedTexture.h"
#include "PhysicsManager.h"
#include "Enemy.h"

namespace SDL_Framework {

	class RedShip :
		public Enemy{

	public:

		//void Update() override;
		//void Render() override;

		void SetVisible(bool visible);
		bool IsVisible();
		bool IsAnimating();

		static void CreateDivePaths();

		void Dive(int type = 0) override;

		void Hit(PhysEntity* other) override;
		bool IgnoreCollision(PhysEntity* Entity);

		RedShip(int path, int index, bool challenge);
		~RedShip();

		//virtual void Render() override;

	private:
		static std::vector<std::vector<Vector2>> sDivePaths;

		static const int MAX_BULLETS = 2;
		Bullet* mBullets[MAX_BULLETS];

		Texture* mRedShip;
		PhysEntity* mCollider;
		AnimatedTexture* mDeathAnimation;

		bool mVisible;
		bool mAnimating;
		bool mEscort;

		Vector2 LocalFormationPosition() override;

		//void HandleFiring();

		void HandleDiveState() override;

		void RenderDiveState() override;
	};
}