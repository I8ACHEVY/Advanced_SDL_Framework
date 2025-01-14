#include "RedShip.h"
#include "BoxCollider.h"
#include "AudioManager.h"

std::vector<std::vector<Vector2>> RedShip::sDivePaths;

void RedShip::CreateDivePaths() {
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

	currentPath = 2;		//escort path
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

void RedShip::Dive(int type) {
	mEscort = type != 0;

	Enemy::Dive();
}

Vector2 RedShip::LocalFormationPosition() {
	Vector2 retVal;
	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x =
		(sFormation->GridSize().x + sFormation->GridSize().x *
			2 * (mIndex / 2)) * (float)dir;
	retVal.y = -sFormation->GridSize().y * 2.2;

	return retVal;
}

void RedShip::HandleDiveState() {
	int currentPath = mIndex % 2;

	if (mEscort) {
		currentPath += 2;
	}

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

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			JoinFormation();
		}
	}

}

void RedShip::Hit(PhysEntity* other) {
	AudioManager::Instance()->PlaySFX("PlayerExplosion.wav", 0, -1);
	sPlayer->AddScore(mCurrentState == Enemy::InFormation ? 80 : 160);
	Enemy::Hit(other);
}

void RedShip::RenderDiveState() {
	int currentPath = mIndex % 2;

	if (mEscort) {
		currentPath += 2;
	}

	mTexture[0]->Render();

	Vector2 finalPos = WorldFormationPosition();
	auto currentDivePath = sDivePaths[currentPath];
	Vector2 pathEndPos = mDiveStartPosition + currentDivePath[currentDivePath.size() - 1];

}

RedShip::RedShip(int path, int index, bool challenge) :
	Enemy(path, index, challenge) {

	mTag = "RedShip";

	//if (mCaptureBeam && mCaptureBeam->Zombie()) {
		mTexture[0] = new Texture("PlayerShips.png", 60, 0, 60, 64);
		mTexture[1] = new Texture("PlayerShips.png", 60, 0, 60, 64);
	//}
	//else {
	//	mTexture[0] = new Texture("PlayerShips.png", 60, 64, 60, 64);
	//	mTexture[1] = new Texture("PlayerShips.png", 60, 64, 60, 64);
	//}

	for (auto texture : mTexture) {
		texture->Parent(this);
		texture->Position(Vec2_Zero);
		texture->Scale(Vector2(0.7f, 0.7f));
	}

	mType = Enemy::RedShips;

	//if (mCaptureBeam && mCaptureBeam->Zombie()) {
		AddCollider(new BoxCollider(Vector2(10.0f, 45.0f)));
		AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(12.0f, 5.0f));
		AddCollider(new BoxCollider(Vector2(18.0f, 32.0f)), Vector2(-12.0f, 5.0f));
	//}

	//mId = PhysicsManager::Instance()->RegisterEntity(this,
	//
	//	PhysicsManager::CollisionLayers::Hostile);

	//mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f,
	//	AnimatedTexture::Horizontal);
	//
	//mDeathAnimation->Parent();
	//mDeathAnimation->Position(Vec2_Zero);
	//mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	for (int i = 0; i < MAX_BULLETS; i++) {
		mBullets[i] = new Bullet(true);
	}
}

RedShip::~RedShip() {
	if (mCollider) {
		delete mCollider;
		mCollider = nullptr;
	}

	//if (mDeathAnimation) {
	//	delete mDeathAnimation;
	//	mDeathAnimation = nullptr;
	//}

	for (auto bullet : mBullets) {
		delete bullet;
		bullet = nullptr;
	}
}

void RedShip::CapturedPlayer() {
	if (mCaptureBeam->Zombie())
	UpdateTexture(mIndex);
}

void RedShip::UpdateTexture(int index) {
	if (index == mBossIndex + 1) {
		if (mCaptureBeam->Zombie()) {
			mTexture[0] = new Texture("PlayerShips.png", 60, 0, 60, 64);
			mTexture[1] = new Texture("PlayerShips.png", 60, 0, 60, 64);
		}

		for (auto texture : mTexture) {
			texture->Parent(this);
			texture->Position(Vec2_Zero);
			texture->Scale(Vector2(0.7f, 0.7f));
		}
	}
}

bool RedShip::IgnoreCollision(PhysEntity* Entity) {
	return !mCaptureBeam->Zombie() || !Active();
}

/* XML RedShip flyIn spawning

<Spawn path="0" priority="5">
	<Enemy type="RedShip" index="0"/>
</Spawn>

<Spawn path="1" priority="5">
	<Enemy type="RedShip" index="1"/>
</Spawn>

<Spawn path="2" priority="5">
	<Enemy type="RedShip" index="2"/>
</Spawn>

<Spawn path="3" priority="5">
	<Enemy type="RedShip" index="3"/>
</Spawn>

*/