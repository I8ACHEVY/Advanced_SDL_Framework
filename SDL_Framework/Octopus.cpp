#include "Octopus.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Octopus::sDivePaths;

void Octopus::CreateDivePaths() {
	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(Vec2_Zero),
		Vector2(0.0f, -45.0f),
		Vector2(-60.0f, -45.0f),
		Vector2(-60.0f, 0.0f) }, 15
		);

	path->AddCurve({
		Vector2(-60.0f, 0.0f),
		Vector2(-60.0f, 80.0f),
		Vector2(0.0f, 150.0f),
		Vector2(100.0f, 150.0f) }, 15
		);

	path->AddCurve({
		Vector2(100.0f, 150.0f),
		Vector2(250.0f, 150.0f),
		Vector2(250.0f, 200.0f),
		Vector2(250.0f, 250.0f) }, 15
		);

	path->AddCurve({
		Vector2(250.0f, 250.0f),
		Vector2(250.0f, 450.0f),	
		Vector2(50.0f, 500.0f),
		Vector2(50.0f, 350.0f) }, 15
		);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);

	delete path;

	currentPath++;

	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(60.0f, -45.0f),
		Vector2(60.f, 0.0f) }, 15
		);

	path->AddCurve({
		Vector2(60.0f, 0.0f),
		Vector2(60.0f, 80.0f),
		Vector2(0.0f, 150.0f),
		Vector2(-100.0f, 150.0f) }, 15
		);

	path->AddCurve({
		Vector2(-100.0f, 150.0f),
		Vector2(-250.0f, 150.0f),
		Vector2(-250.0f, 200.0f),
		Vector2(-250.0f, 250.0f) }, 15
		);

	path->AddCurve({
		Vector2(-250.0f, 250.0f),
		Vector2(-250.0f, 450.0f),
		Vector2(-50.0f, 500.0f),
		Vector2(-50.0f, 350.0f) }, 15
		);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

void Octopus::FlyInComplete() {
	if (mDiver) {
		mCurrentState = Dead;
	}
	else {
		JoinFormation();
	}
}

Vector2 Octopus::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * 2 + sFormation->GridSize().y * 
		((mIndex % 4) / 2);

	return retVal;
}

void Octopus::HandleDiveState() {
	int currentPath = mIndex % 2;

	if (mCurrentWayPoint < sDivePaths[currentPath].size() && 
		!sPlayer->IsAnimating() && sPlayer->IsVisible()) {

		Vector2 waypointPos = mDiveStartPosition + sDivePaths
			[currentPath][mCurrentWayPoint];

		Vector2 dist = waypointPos - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);

		if (sPlayer->IsVisible()) {

			Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
		}

		if ((waypointPos - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25) {
			mCurrentWayPoint++;
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25) {
			JoinFormation();
		}
	}
}

void Octopus::RenderDiveState() {
	mTexture[0]->Render();

	int currentPath = mIndex % 2;	
	
	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];

}

void Octopus::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("WaspDestroyed.wav", 0, -1);
	sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 50 : 100);

	Enemy::Hit(other);
}

Octopus::Octopus(int path, int index, bool challenge, bool diver) :
	Enemy(path, index, challenge), mDiver(diver) {

	mTag = "Octopus";

	mTexture[0] = new Texture("InvaderSprites.png", 147, 226, 26, 24);
	mTexture[1] = new Texture("InvaderSprites.png", 179, 226, 26, 24);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(1.7f, 1.7f));

	}

		mType = Enemy::Octopus;

		//AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Octopus::~Octopus() {

}
