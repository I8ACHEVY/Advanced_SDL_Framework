#include "Squid.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Squid::sDivePaths;

void Squid::CreateDivePaths() {
	int currentPath = 0;
	BezierPath* path = new BezierPath();

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
		Vector2(200.0f, 710.0f),
		Vector2(200.0f, 510.0f) }, 15);	

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;

	currentPath = 1;
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
		Vector2(-200.0f, 540.0f) }, 15);

	path->AddCurve({
		Vector2(-200.0f, 540.0f),
		Vector2(-200.0f, 540.0f),
		Vector2(-200.0f, 710.0f),
		Vector2(-200.0f, 510.0f) }, 15);		

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
		Vector2(75.0f, 140.0f),
		Vector2(75.0f, 250.0f) }, 15);

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
		Vector2(-100.0f, 340.0f),
		Vector2(-100.0f, 400.0f) }, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);
	delete path;
}

void Squid::Dive(int type) {
	//mCaptureDive = type != 0;

	Enemy::Dive();

	mCurrentPath = mIndex % 2;
}

void Squid::Hit(PhysEntity* other) {
	if (mWasHit) {
		Enemy::Hit(other);
		AudioManager::Instance()->PlaySFX("BossDestroyed.wav", 0, 2);
		sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 150 : 400);
		Enemy::Hit(other);
	}
	else {
		mWasHit = true;
		SDL_Rect temp = { 0, 64, 60, 64 };
		mTexture[0]->SetSourceRect(&temp);
		temp.x = 66;
		temp.y = 68;
		mTexture[1]->SetSourceRect(&temp);
		AudioManager::Instance()->PlaySFX("BossInjured.wav", 0, -1);
	}
}

Vector2 Squid::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y;

	return retVal;
}

void Squid::HandleDiveState() {
	
	if (mCurrentWayPoint < sDivePaths[mCurrentPath].size() &&
		!sPlayer->IsAnimating() && sPlayer->IsVisible()) {

		Vector2 waypointPos = mDiveStartPosition + sDivePaths
			[mCurrentPath][mCurrentWayPoint];

		Vector2 dist = waypointPos - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);

		if (sPlayer->IsVisible()) {

			Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
		}

		if ((waypointPos - Position()).MagnitudeSqr() < EPSILON * mSpeed / 25) {
			mCurrentWayPoint++;
		}
	}
}

void Squid::RenderDiveState() {
	mTexture[0]->Render();

	int currentPath = mIndex % 2;
	
	//for (int i = 0; i < sDivePaths[currentPath].size() - 1; i++) {		// Dive path debugging
	//	Graphics::Instance()->DrawLine(
	//		mDiveStartPosition.x + sDivePaths[currentPath][i].x,
	//		mDiveStartPosition.y + sDivePaths[currentPath][i].y,
	//		mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x,
	//		mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y
	//	);
	//}
	
	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];
	
	//Graphics::Instance()->DrawLine(		//return path debugging
	//	pathEndPos.x,
	//	pathEndPos.y,
	//	finalPos.x,
	//	finalPos.y
	//);
	
}

Squid::Squid(int path, int index, bool challenge) ://squid
	Enemy(path, index, challenge){

	mTag = "Squid";

	mTexture[0] = new Texture("InvaderSprites.png", 7, 225, 18, 18);
	mTexture[1] = new Texture("InvaderSprites.png", 40, 225, 18, 18);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(1.7f, 1.7f));
	}

	mType = Enemy::Squid;

	mCurrentPath = 0;

	AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));

	mWasHit = false;
}

Squid::~Squid() {

}