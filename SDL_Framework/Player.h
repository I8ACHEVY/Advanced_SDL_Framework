#pragma once
#include "PhysicsEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BoxCollider.h"

using namespace SDL_Framework;

class Player : public PhysEntity {

public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

	void Visible(bool visible);

	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void WasHit();

	bool IgnoreCollision() override;
	void Hit(PhysEntity* other) override;

private:
	bool mWasHit;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	Texture* mShip;
	AnimatedTexture* mDeathAnimation;

	int mScore;
	int mLives;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
};