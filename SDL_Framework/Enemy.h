#pragma once

#include "BezierPath.h"
#include "GLAnimatedTexture.h"
#include "PhysicsEntity.h"
#include "Player.h"
#include "Formation.h"
#include "Bullet.h"

using namespace SDL_Framework;

class Enemy : public PhysEntity {
public:
	enum States { FlyIn, InFormation, Diving, Dead };
	enum Types { Crab, Octopus, Squid, RedShips};

	//static void CreatePaths();
	static void SetFormation(Formation* formation);
	static void CurrentPlayer(Player* player);

	States CurrentState();
	Types Type();
	int Index();

	Enemy(int Index, bool Challenge);
	virtual ~Enemy();

	//virtual void Dive(int type = 0);
	virtual void Hit(PhysEntity* other) override;
	bool InDeathAnimation();

	void Update() override;
	virtual void Render() override;

protected:
	static Formation* sFormation;
	static std::vector<std::vector<Vector2>> sPaths;
	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTexture[2];

	GLAnimatedTexture* mDeathAnimation;

	States mCurrentState;

	Types mType;

	int mIndex;

	bool mChallengeStage;

	//Vector2 mDiveStartPosition;

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
	//virtual void HandleDiveState() = 0;
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderInFormationState();
	//virtual void RenderDiveState() = 0;
	virtual void RenderDeadState();

	void RenderStates();

	bool IgnoreCollision() override;

	void HandleFiring();
	void FireBullet(Vector2 position, Vector2 direction);
	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];
	//AudioManager* mAudio;
};