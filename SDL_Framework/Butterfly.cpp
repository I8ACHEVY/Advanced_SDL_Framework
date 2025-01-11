#include "Butterfly.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Butterfly::sDivePaths;

void Butterfly::CreateDivePaths() {
	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -45.0f),
		Vector2(-60.0f, -45.0f),
		Vector2(-60.f, 0.0f) }, 15
		);

	path->AddCurve({
		Vector2(-60.0f, 0.0f),
		Vector2(-60.0f, 80.0f),
		Vector2(200.0f, 125.0f),
		Vector2(200.0f, 200.0f) }, 15
		);

	path->AddCurve({
		Vector2(200.0f, 200.0f),
		Vector2(200.0f, 275.0f),
		Vector2(175.0f, 250.0f),
		Vector2(175.0f, 325.0f) }, 15
		);

	path->AddCurve({
		Vector2(175.0f, 325.0f),
		Vector2(175.0f, 425.0f),
		Vector2(375.0f, 425.0f),
		Vector2(375.0f, 525.0f) }, 15
		);

	path->AddCurve({
		Vector2(375.0f, 525.0f),
		Vector2(375.0f, 575.0f),
		Vector2(300.0f, 615.0f),
		Vector2(300.0f, 560.0f) }, 15
		);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 1;
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
		Vector2(-200.0f, 125.0f),
		Vector2(-200.0f, 200.0f) }, 15
		);

	path->AddCurve({
		Vector2(-200.0f, 200.0f),
		Vector2(-200.0f, 275.0f),
		Vector2(-175.0f, 250.0f),
		Vector2(-175.0f, 325.0f) }, 15
		);

	path->AddCurve({
		Vector2(-175.0f, 325.0f),
		Vector2(-175.0f, 425.0f),
		Vector2(-375.0f, 425.0f),
		Vector2(-375.0f, 525.0f) }, 15
		);

	path->AddCurve({
		Vector2(-375.0f, 525.0f),		
		Vector2(-375.0f, 575.0f),		
		Vector2(-300.0f, 615.0f),		
		Vector2(-300.0f, 560.0f) }, 15	
		);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 2;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -60.0f),
		Vector2(-90.0f, -60.0f),
		Vector2(-90.0f, 0.0f) }, 15);

	path->AddCurve({
		Vector2(-90.0f, 0.0f),
		Vector2(-90.0f, 60.0f),
		Vector2(-100.0f, 272.0f),
		Vector2(-15.0f, 275.0f) }, 15);

	path->AddCurve({
		Vector2(-15.0f, 275.0f),
		Vector2(85.0f, 275.0f),
		Vector2(85.0f, 125.0f),
		Vector2(-15.0f, 125.0f) }, 15);

	path->AddCurve({
		Vector2(-15.0f, 125.0f),
		Vector2(-175.0f, 125.0f),
		Vector2(0.0f, 450.0f),
		Vector2(125.0f, 450.0f) }, 25);

	path->AddCurve({
		Vector2(120.0f, 450.0f),
		Vector2(160.0f, 450.0f),
		Vector2(200.0f, 500.0f),
		Vector2(200.0f, 550.0f) }, 15);

	path->AddCurve({
		Vector2(200.0f, 550.0f),
		Vector2(200.0f, 540.0f),
		Vector2(200.0f, 810.0f),
		Vector2(200.0f, 510.0f) }, 15);	

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 3;
	path = new BezierPath();

	path->AddCurve({
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, -60.0f),
		Vector2(90.0f, -60.0f),
		Vector2(90.0f, 0.0f) }, 15);

	path->AddCurve({
		Vector2(90.0f, 0.0f),
		Vector2(90.0f, 60.0f),
		Vector2(100.0f, 272.0f),
		Vector2(15.0f, 275.0f) }, 15);

	path->AddCurve({
		Vector2(15.0f, 275.0f),
		Vector2(-85.0f, 275.0f),
		Vector2(-85.0f, 125.0f),
		Vector2(15.0f, 125.0f) }, 15);

	path->AddCurve({
		Vector2(15.0f, 125.0f),
		Vector2(175.0f, 125.0f),
		Vector2(0.0f, 450.0f),
		Vector2(-125.0f, 450.0f) }, 25);

	path->AddCurve({
		Vector2(-120.0f, 450.0f),
		Vector2(-160.0f, 450.0f),
		Vector2(-200.0f, 500.0f),
		Vector2(-200.0f, 550.0f) }, 15);

	path->AddCurve({
		Vector2(-200.0f, 550.0f),
		Vector2(-200.0f, 540.0f),
		Vector2(-200.0f, 810.0f),
		Vector2(-200.0f, 510.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

void Butterfly::Dive(int type) {
	mEscort = type != 0;

	Enemy::Dive();
}

Vector2 Butterfly::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 
		2 * (mIndex / 4)) * (float)dir;

	retVal.y = sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Butterfly::HandleDiveState(){
	int currentPath = mIndex % 2;

	if (mEscort) {
		currentPath += 2;
	}

	if (mCurrentWayPoint < sDivePaths[currentPath].size() && 
		!sPlayer->IsAnimating() && sPlayer->IsVisible()){

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

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			JoinFormation();
		}
	}

}

void Butterfly::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("ButterflyDestroyed.wav", 0, -1); 
	sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 80 : 160);
	Enemy::Hit(other);
}

void Butterfly::RenderDiveState(){
	int currentPath = mIndex % 2;

	if (mEscort) {
		currentPath += 2;
	}

	mTexture[0]->Render();
	
	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];
	
}

Butterfly::Butterfly(int path, int index, bool challenge) :
Enemy(path, index, challenge) 
{
	mTag = "Butterfly";

	mTexture[0] = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture[1] = new Texture("AnimatedEnemies.png", 52, 0, 52, 40);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(0.7f, 0.7f));
	}
	
	mType = Enemy::Butterfly;

	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));
}

Butterfly::~Butterfly() {}
