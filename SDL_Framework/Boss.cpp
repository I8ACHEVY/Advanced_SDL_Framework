#include "Boss.h"

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
		Vector2(200.0f, 810.0f),
		Vector2(200.0f, 800.0f) }, 15);

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
		Vector2(-200.0f, 550.0f) }, 15);

	path->AddCurve({
		Vector2(-200.0f, 550.0f),
		Vector2(-200.0f, 540.0f),
		Vector2(-200.0f, 810.0f),
		Vector2(-200.0f, 800.0f) }, 15);

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
		Vector2(100.0f, 340.0f),
		Vector2(100.0f, 400.0f) }, 15);

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

	//if (mCaptureDive) {
	//	mCapturing = false;
	//	mCurrentPath = 2 + Random::Instance()->RandomRange(0, 1);
	//	mCaptureBeam->ResetAnimation();
	//}
	//else {
	//	mCurrentPath = mIndex % 2;
	//}
}

Vector2 Boss::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y =
		-sFormation->GridSize().y;

	return retVal;
}

void Boss::HandleDiveState() {
	int currentPath = mIndex % 2;
	
	if (mCaptureDive) {
		currentPath += 2;
	}
	
	if (mCurrentWayPoint < sDivePaths[currentPath].size()) {
		Vector2 waypointPos = mDiveStartPosition + sDivePaths
			[mCurrentPath][mCurrentWayPoint];
	
		Vector2 dist = waypointPos - Position();
	
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);
	
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

void Boss::HandleDeadState() {

}

void Boss::RenderDiveState() {
	int currentPath = mIndex % 2;
	
	if (mCaptureDive) {
		currentPath += 2;
	}
	
	mTexture[sFormation->GetTick() % 2]->Render();
	
	for (int i = 0; i < sDivePaths[currentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(
			mDiveStartPosition.x + sDivePaths[currentPath][i].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i].y,
			mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y
		);
	}
	
	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];
	
	Graphics::Instance()->DrawLine(
		pathEndPos.x,
		pathEndPos.y,
		finalPos.x,
		finalPos.y
	);
}

void Boss::RenderDeadState() {

}

Boss::Boss(int path, int index, bool challenge) :
	Enemy(path, index, challenge) {

	mTexture[0] = new Texture("Bosses.png", 0, 0, 64, 64);
	mTexture[1] = new Texture("Bosses.png", 64, 0, 64, 64);

	for (int i = 0; i < 2; i++) {
		mTexture[i]->Parent(this);
		mTexture[i]->Position(Vec2_Zero);
	}

	mType = Enemy::Boss;

	mCurrentPath = 0;
}

Boss::~Boss() {

}