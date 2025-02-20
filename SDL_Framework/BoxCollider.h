#pragma once
#include "Collider.h"

namespace SDL_Framework {

	class BoxCollider : public Collider {
	public:
		BoxCollider(Vector2 size);
		~BoxCollider();

		Vector2 GetFurthestPoint() override;

	private:
		static const int MAX_VERTS = 4;

		GameEntity* mVerts[MAX_VERTS];

		void AddVert(int index, Vector2 pos);
	};
}