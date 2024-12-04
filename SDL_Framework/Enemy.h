#pragma once

#include "BezierPath.h"
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"
#include "Player.h"

using namespace SDL_Framework;

class Enemy : public PhysEntity {
public:
	enum States {FlyIn, InFormation, Diving, Dead};

	static void CreatePaths();

	States CurrentState();

	Enemy(int path);
	virtual ~Enemy();

	void Update() override;
	void Render() override;

protected:
	static std::vector<std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture;

	States mCurrentState;

	unsigned mCurrentPath;

	unsigned mCurrentWayPoint;
	const float EPSILON = 50.0f;

	float mSpeed;

	virtual void HandleFlyInState();
	virtual void HandleInFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	virtual void RenderDiveState();
	virtual void RenderDeadState();

	void RenderStates();
};