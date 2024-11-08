#pragma once
#include "MathHelper.h"

namespace SDL_Framework {
	class GameEntity {
	public:
		enum Space { Local = 0, World};

		GameEntity(float x = 0.0f, float y = 0.0f);
		~GameEntity();

		void Position(float x, float y);
		void Position(const Vector2& pos);
		Vector2 Position(Space space = World);

		void Rotation(float rot);
		float Rotation(Space space = World);

		void Scale(Vector2 scale);
		Vector2 Scale(Space space = World);

		void Active(bool active);
		bool Active();

		void Parent(GameEntity* parent);
		GameEntity* Parent();

		virtual void Update() {};
		virtual void Render() {};

	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	};
}