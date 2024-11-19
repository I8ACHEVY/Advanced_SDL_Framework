#pragma once
#include "Collider.h"
#include <vector>

namespace SDL_Framework{
	
	class PhysEntity : public GameEntity {
	public:
		PhysEntity();
		virtual ~PhysEntity();

		unsigned long GetId();

		bool CheckCollision(PhysEntity* other);

		virtual void Hit(PhysEntity* other);

		virtual void Render() override;

	protected:
		unsigned long mId;

		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;

		virtual bool IgnoreCollision();
		
		void AddCollider(Collider* collider, Vector2 localPos = vec2_Zero);
	};

}