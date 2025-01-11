#pragma once
#include "AnimatedTexture.h"
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
	bool IsCaptured() const;

	bool IgnoreCollision() override;
	void Hit(PhysEntity* other) override;
	//void HandleCaptureMovement();

private:
	static const int MAX_BULLETS = 2;
	Bullet* mBullets[MAX_BULLETS];

	bool mWasHit;
	//Vector2 mOriginalPosition;
	//float mOriginalRotation;
	bool mIsCaptured;

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
	void HandleFiring();
};