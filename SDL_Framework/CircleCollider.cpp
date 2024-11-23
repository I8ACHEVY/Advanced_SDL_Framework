#include "CircleCollider.h"

namespace SDL_Framework {

	CircleCollider::CircleCollider(float radius, bool broadPhase) :
		Collider(ColliderType::Circle) {

		mRadius = radius;

		if (DEBUG_COLLIDERS) {
			if (broadPhase) {
				SetDebugTexture(new Texture("BroadPhaseCollider.png"));
			}

			else {
				SetDebugTexture(new Texture("CircleCollider.png"));
			}

			mDebugTexture->Scale(Vec2_One * (radius * 2 / 50.0f));
		}
	}
	CircleCollider::~CircleCollider(){}

	Vector2 CircleCollider::GetFurthestPoint() {
		Vector2 localPos = Position(GameEntity::Local);
	    return Vec2_Right * (mRadius + Position(GameEntity::Local)).Magnitude(); //return localPos + Vec2_Right * mRadius; //
	}

	float CircleCollider::GetRadius() {
		return mRadius;
	}
}