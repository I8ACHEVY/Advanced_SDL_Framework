#pragma once
#include "GLAnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BoxCollider.h"
#include "Bullet.h"

using namespace SDL_Framework;

class Player : public PhysEntity {

public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

	void SetVisible(bool visible);
	bool IsVisible();

	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	bool WasHit();

	bool IgnoreCollision() override;
	void Hit(PhysEntity* other) override;

private:
	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

	bool mWasHit;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	Texture* mTank;
	GLAnimatedTexture* mDeathAnimation;

	int mScore;
	int mLives;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
	void HandleFiring();
};