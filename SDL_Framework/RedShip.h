#pragma once
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "PhysicsManager.h"
#include "MathHelper.h"
#include "Formation.h"

namespace SDL_Framework {

	class RedShip :
		//public Texture,
		public PhysEntity {

	public:

		void Hit(PhysEntity* other) override;
		//bool IgnoreCollision(PhysEntity* Entity);

		RedShip();
		~RedShip();

		virtual void Render() override;

	private:

		Texture* mRedShip;
		PhysEntity* mCollider;
		AnimatedTexture* mDeathAnimation;
	};
}