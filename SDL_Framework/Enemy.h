#pragma once

#include "BezierPath.h"
#include "AnimatedTexture.h"
#include "PhysicsEntity.h"
#include "Player.h"
#include "Formation.h"

using namespace SDL_Framework;

class Enemy : public PhysEntity {
public:
	enum States {FlyIn, InFormation, Diving, Dead};
	enum Types {Butterfly, Wasp, Boss};

	static void CreatePaths();
	static void SetFormation(Formation* formation);

	States CurrentState();
	Types Type();
	int Index();

	Enemy(int path, int Index, bool Challenge);
	virtual ~Enemy();

	virtual void Dive(int type = 0);

	void Update() override;
	void Render() override;

protected:
	static Formation* sFormation;
	static std::vector<std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture;

	States mCurrentState;

	Types mType;

	int mIndex;

	bool mChallengeStage;

	Vector2 mDiveStartPosition;

	unsigned mCurrentPath;

	unsigned mCurrentWayPoint;
	const float EPSILON = 50.0f;

	float mSpeed;

	virtual void PathComplete();
	virtual void FlyInComplete();

	void JoinFormation();

	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleInFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState() = 0;

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState() = 0;

	void RenderStates();
};