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

		virtual void Hit(PhysEntity* other){
			std::cout << "Collision Occured" << std::endl;
		}

		virtual void Render() override;

		void Tag(const std::string& tag);
		std::string GetTag() const;

		Collider* GetBroadPhaseCollider() const;
		Collider* GetNarrowPhaseCollider() const;

	protected:
		std::vector<Collider*> mColliders;
		std::string mTag;

		Collider* mBroadPhaseCollider;
		Collider* mNarrowPhaseCollider;

		virtual bool IgnoreCollision();

		unsigned long mId;
		
		void AddCollider(Collider* collider, Vector2 localPos = Vec2_Zero);
	};

}