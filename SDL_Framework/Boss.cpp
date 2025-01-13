#include "Boss.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> Boss::sDivePaths;

void Boss::CreateDivePaths() {
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

void Boss::Dive(int type) {
	mCaptureDive = type != 0;

	Enemy::Dive();

	if (mCaptureDive) {
		mCapturing = false;
		mCurrentPath = 2 + Random::Instance()->RandomRange(0, 1);
		mCaptureBeam->ResetAnimation();
	}
	else {
		mCurrentPath = mIndex % 2;
	}
}

void Boss::Hit(PhysEntity* other) {
	if (mWasHit) {
		Enemy::Hit(other);
		AudioManager::Instance()->PlaySFX("BossDestroyed.wav", 0, 2);
		sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 150 :
			mCaptureDive ? 400 : 800);
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

Vector2 Boss::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y;

	return retVal;
}

void Boss::HandleDiveState() {
	
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

		if (mCurrentWayPoint == sDivePaths[mCurrentPath].size()) {
			if (mCaptureDive) {
				mCapturing = true;
				Rotation(180.0f);
			}
			else {
				Position(Vector2(WorldFormationPosition().x, 20.0f));
			}
		}
	}
	else {
		if (!mCaptureDive || !mCapturing) {
			Vector2 dist = WorldFormationPosition() - Position();

			Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
			Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

			if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25) {
				JoinFormation();
			}
		}
		else {
			HandleCaptureBeam();
		}
	}
}

void Boss::HandleCaptureBeam() {
	mCaptureBeam->PhysEntity::Update();
	mCaptureBeam->AnimatedTexture::Update();

	if (!mCaptureBeam->IsAnimating()) {
		Translate(Vec2_Up * mSpeed * mTimer->DeltaTime(), World);
		if (Position().y >= 580.0f) {
			Position(WorldFormationPosition().x, -20.0f);
			mCapturing = false;
		}
	}
}

void Boss::RenderDiveState() {
	mTexture[0]->Render();

	if (mCapturing && mCaptureBeam->IsAnimating()) {
		//mCaptureBeam->Render();
	}

	int currentPath = mIndex % 2;
	
	if (mCaptureDive) {
		currentPath += 2;
	}
	
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

Boss::Boss(int path, int index, bool challenge) :
	Enemy(path, index, challenge){

	mTag = "Boss";

	mTexture[0] = new Texture("Bosses.png", 0, 0, 64, 64);
	mTexture[1] = new Texture("Bosses.png", 64, 0, 64, 64);

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(0.7f, 0.7f));
	}

	mType = Enemy::Boss;

	mCurrentPath = 0;

	mCaptureDive = false;
	mCurrentPath = 0;
	mCapturing = false;

	mCaptureBeam = new CaptureBeam();
	mCaptureBeam->PhysEntity::Parent(this);
	mCaptureBeam->PhysEntity::Position(0.0f, -140.0f);
	mCaptureBeam->PhysEntity::Rotation(180.0f);

	mCaptureBeam->AnimatedTexture::Parent(this);
	mCaptureBeam->AnimatedTexture::Position(0.0f, -140.0f);
	mCaptureBeam->AnimatedTexture::Rotation(180.0f);

	//AddCollider(new BoxCollider(mTexture[1]->ScaledDimensions()));

	mWasHit = false;
}

Boss::~Boss() {
	delete mCaptureBeam;
	mCaptureBeam = nullptr;
}