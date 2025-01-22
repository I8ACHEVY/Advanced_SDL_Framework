#include "Crab.h"
#include "BoxCollider.h"
#include "AudioManager.h"

Vector2 Crab::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Crab::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("ButterflyDestroyed.wav", 0, -1); 
	sPlayer->AddScore(20);
	Enemy::Hit(other);
}

Crab::Crab(int index, bool challenge) :
Enemy(index, challenge) 
{
	mTag = "Crab";

	mTexture[0] = new GLTexture("InvaderSprites.png", 74, 225, 24, 24);
	mTexture[1] = new GLTexture("InvaderSprites.png", 107, 225, 24, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));
	}
	
	mType = Enemy::Crab;

	//AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Crab::~Crab() {}
