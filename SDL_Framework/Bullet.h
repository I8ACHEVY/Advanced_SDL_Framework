#pragma once

#include "PhysicsEntity.h"
#include "Timer.h"

using namespace SDL_Framework;

class Bullet : public PhysEntity {
public:
	Bullet(bool friendly);
	~Bullet();

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* other) override;

	void Fire(Vector2 pos);
	void Reload();

private:
	bool IgnoreCollision() override;

	static const int OFFSCREEN_BUFFER = 180;	
	Timer* mTimer;
	Texture* mTexture;
	float mSpeed;
};