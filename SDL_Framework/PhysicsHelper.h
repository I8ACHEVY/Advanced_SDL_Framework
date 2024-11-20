#pragma once
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"

namespace SDL_Framework {
	inline bool CircleVsCircleCollision(CircleCollider* circle1,
		CircleCollider* circle2) {

		return (circle1->Position() - circle2->Position()).Magnitude()
			< (circle1->GetRadius() + circle2->GetRadius());
	}



}