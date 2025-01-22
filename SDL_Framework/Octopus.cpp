#include "Octopus.h"
#include "BoxCollider.h"
#include "AudioManager.h"

Vector2 Octopus::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * 2 + sFormation->GridSize().y * 
		((mIndex % 4) / 2);

	return retVal;
}

void Octopus::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("WaspDestroyed.wav", 0, -1);
	sPlayer->AddScore(10);

	Enemy::Hit(other);
}

Octopus::Octopus(int index, bool challenge) :
	Enemy(index, challenge){

	mTag = "Octopus";

	mTexture[0] = new GLTexture("InvaderSprites.png", 147, 226, 26, 24);
	mTexture[1] = new GLTexture("InvaderSprites.png", 179, 226, 26, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		//texture->Scale(Vector2(1.7f, 1.7f));

	}

		mType = Enemy::Octopus;

		//AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Octopus::~Octopus() {

}
