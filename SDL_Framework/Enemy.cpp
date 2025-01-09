#include "Enemy.h"
#include "PhysicsManager.h"

std::vector<std::vector<Vector2>>Enemy::sPaths;
Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenXPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.46f);
	int screenYPoint = (int)(Graphics::Instance()->SCREEN_HEIGHT * 0.25f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f) }, 1
	);

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 100.0f),
		Vector2( 320.0f, screenYPoint + 140.0f),
		Vector2( 320.0f, screenYPoint + 300.0f) }, 25
	);

	path->AddCurve({
		Vector2( 320.0f, screenYPoint + 300.0f),
		Vector2( 320.0f, screenYPoint + 500.0f),
		Vector2( 580.0f, screenYPoint + 600.0f),
		Vector2( 580.0f, screenYPoint + 340.0f) }, 25
	);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

/*	currentPath = 6;			//edit to be top left hook
	path = new BezierPath();
	int fullScreen = screenXPoint * 0.8;

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f) }, 1
		);

	path->AddCurve({
		Vector2(screenXPoint + 150.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint + 150.0f, screenYPoint + 100.0f),
		Vector2(320.0f, screenYPoint + 140.0f),
		Vector2(320.0f, screenYPoint + 300.0f) }, 25
		);

	path->AddCurve({
		Vector2(320.0f, screenYPoint + 300.0f),
		Vector2(320.0f, screenYPoint + 500.0f),
		Vector2(580.0f, screenYPoint + 600.0f),
		Vector2(580.0f, screenYPoint + 340.0f) }, 25
		);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
	*/

	currentPath = 1;
	path = new BezierPath();
	int fullScreen = screenXPoint * 0.8;

	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f) }, 1);
	
	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 80.0f),
		Vector2( 1070.0f, screenYPoint + 140.0f),
		Vector2( 1070.0f, screenYPoint + 300.0f) }, 25);
	
	path->AddCurve({
		Vector2( 1070.0f, screenYPoint + 300.0f),
		Vector2( 1070.0f, screenYPoint + 500.0f),
		Vector2( 830.0f, screenYPoint + 600.0f),
		Vector2( 830.0f, screenYPoint + 340.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

/*	currentPath = 7;			//edit to be top right hook
	path = new BezierPath();

	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + -10.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + -20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 30.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f) }, 1);

	path->AddCurve({
		Vector2(screenXPoint - 50.0f, screenYPoint + 20.0f),
		Vector2(screenXPoint - 50.0f, screenYPoint + 80.0f),
		Vector2(1070.0f, screenYPoint + 140.0f),
		Vector2(1070.0f, screenYPoint + 300.0f) }, 25);

	path->AddCurve({
		Vector2(1070.0f, screenYPoint + 300.0f),
		Vector2(1070.0f, screenYPoint + 500.0f),
		Vector2(830.0f, screenYPoint + 600.0f),
		Vector2(830.0f, screenYPoint + 340.0f) }, 25);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
	*/

	currentPath = 2;
	float temp = screenXPoint - 100.0f;

	path = new BezierPath();

	path->AddCurve({
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(400.0f, screenYPoint + 640.0f),
		Vector2(temp, screenYPoint + 500.0f),
		Vector2(temp, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp, screenYPoint + 400.0f),
		Vector2(temp, screenYPoint + 200.0f),
		Vector2(320.0f, screenYPoint + 140.0f),
		Vector2(320.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(320.0f, screenYPoint + 300.0f),
		Vector2(320.0f, screenYPoint + 500.0f),
		Vector2(temp + 40.0f, screenYPoint + 600.0f),
		Vector2(temp + 40.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

	/*currentPath = 4;		// edit to be side by side left bottom
	path = new BezierPath();

	path->AddCurve({
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(280.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(310.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(310.0f, screenYPoint + 640.0f),
		Vector2(400.0f, screenYPoint + 640.0f),
		Vector2(temp, screenYPoint + 500.0f),
		Vector2(temp, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp, screenYPoint + 400.0f),
		Vector2(temp, screenYPoint + 200.0f),
		Vector2(320.0f, screenYPoint + 140.0f),
		Vector2(320.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(320.0f, screenYPoint + 300.0f),
		Vector2(320.0f, screenYPoint + 500.0f),
		Vector2(temp + 40.0f, screenYPoint + 600.0f),
		Vector2(temp + 40.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
	*/

	currentPath = 3;
	temp = screenXPoint + 60.0f;
	float temp2 = fullScreen - 40.0f;

	path = new BezierPath();
	path->AddCurve({
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 510.0f, screenYPoint + 640.0f),
		Vector2(temp + 130, screenYPoint + 500.0f),
		Vector2(temp + 130, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp + 130, screenYPoint + 400.0f),
		Vector2(temp + 130, screenYPoint + 200.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 140.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 500.0f),
		Vector2(temp + 120.0f, screenYPoint + 600.0f),
		Vector2(temp + 120.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;

/*	currentPath = 5;			//edit to be side by side right bottom
	path = new BezierPath();

	path->AddCurve({
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 620.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f) }, 1);

	path->AddCurve({
		Vector2(temp2 + 580.0f, screenYPoint + 640.0f),
		Vector2(temp2 + 510.0f, screenYPoint + 640.0f),
		Vector2(temp + 130, screenYPoint + 500.0f),
		Vector2(temp + 130, screenYPoint + 400.0f) }, 15);

	path->AddCurve({
		Vector2(temp + 130, screenYPoint + 400.0f),
		Vector2(temp + 130, screenYPoint + 200.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 140.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f) }, 15);

	path->AddCurve({
		Vector2(temp2 + 590.0f, screenYPoint + 300.0f),
		Vector2(temp2 + 590.0f, screenYPoint + 500.0f),
		Vector2(temp + 120.0f, screenYPoint + 600.0f),
		Vector2(temp + 120.0f, screenYPoint + 340.0f) }, 15);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
	*/
}

void Enemy::SetFormation(Formation* formation) {
	sFormation = formation;
}

void Enemy::CurrentPlayer(Player* player) {
	sPlayer = player;
}

Enemy::Enemy(int path, int index, bool challenge) :
	mCurrentPath(path), mIndex(index), mChallengeStage(challenge){

	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWayPoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mTexture[0] = nullptr;		// enemy new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture[1] = nullptr;
	
	mSpeed = 450.0f;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mDeathAnimation = new AnimatedTexture("EnemyExplosion.png", 0, 0, 128, 128, 5, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);
}

Enemy::~Enemy() {
	mTimer = nullptr;

	for (int i = 0; i < 2; i++) {
		delete mTexture[i];
		mTexture[i] = nullptr;
	}

	delete mDeathAnimation;
	//mDeathAnimation = nullptr;
}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

Vector2 Enemy::WorldFormationPosition() {
	return sFormation->Position() + LocalFormationPosition();
}

void Enemy::FlyInComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;	//change dead when adding challenge stages
	}
	else {
		JoinFormation();
	}
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::PathComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;	//change dead when adding challenge stages
	}
}

Enemy::Types Enemy::Type() {
	return mType;
}

int Enemy::Index() {
	return mIndex;
}

void Enemy::Dive(int type) {
	Parent(nullptr);
	mCurrentState = Diving;
	mDiveStartPosition = Position();
	mCurrentWayPoint = 1;
}

void Enemy::Update() {
	if (Active()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (Active()) {
		RenderStates();
	}
}

void Enemy::HandleFlyInState() {
	if (mCurrentWayPoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWayPoint] - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((sPaths[mCurrentPath][mCurrentWayPoint] - Position()).MagnitudeSqr()
			< EPSILON * mSpeed / 25.0f) {

			mCurrentWayPoint++;
		}

		if (mCurrentWayPoint >= sPaths[mCurrentPath].size()) {
			PathComplete();
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - Position();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			FlyInComplete();
		}
	}
}

void Enemy::HandleInFormationState() {
	Position(LocalFormationPosition());

	float rotation = Rotation();
	if (rotation != 0.0f) {
		if (rotation > 5.0f) {
			float rotationSpeed = 200.0f;
			float rotationDir = (rotation >= 180.0f) ? 1.0f : -1.0f;
			Rotate(rotationDir * mTimer->DeltaTime() * rotationSpeed);
		}
		else {
			Rotation(0.0f);
		}
	}
}

void Enemy::HandleDeadState() {
	if (mDeathAnimation->IsAnimating()) {
		mDeathAnimation->Update();
	}
}

void Enemy::RenderDeadState() {
	if (mDeathAnimation->IsAnimating()) {
		mDeathAnimation->Render();
	}
}

void Enemy::HandleStates() {
	switch (mCurrentState) {

	case FlyIn:
		HandleFlyInState();
		break;

	case InFormation:
		HandleInFormationState();
		break;

	case Diving: 
		HandleDiveState();
		break;

	case Dead:
		HandleDeadState();
		break;
	}
}

void Enemy::RenderFlyInState() {
	mTexture[0]->Render();
	//mTexture[sFormation->GetTick() % 2]->Render();

	//for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {		// debug paths as they are called
	//	Graphics::Instance()->DrawLine(
	//		sPaths[mCurrentPath][i].x, 
	//		sPaths[mCurrentPath][i].y,
	//		sPaths[mCurrentPath][i + 1].x, 
	//		sPaths[mCurrentPath][i + 1].y
	//	);
	//}
}

void Enemy::RenderInFormationState() {
	mTexture[sFormation->GetTick() % 2]->Render();

	//for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {		// debug bezier paths even after called
	//	Graphics::Instance()->DrawLine(
	//		sPaths[mCurrentPath][i].x,
	//		sPaths[mCurrentPath][i].y,
	//		sPaths[mCurrentPath][i + 1].x,
	//		sPaths[mCurrentPath][i + 1].y
	//	);
	//}
}

void Enemy::RenderStates() {
	switch (mCurrentState) {

	case FlyIn:
		RenderFlyInState();
		break;

	case InFormation:
		RenderInFormationState();
		break;

	case Diving:
		RenderDiveState();
		break;

	case Dead:
		RenderDeadState();
		break;
	}
	PhysEntity::Render();
}

bool Enemy::IgnoreCollision(){
	return mCurrentState == Dead;
}

void Enemy::Hit(PhysEntity* other) {
	if (mCurrentState == InFormation) {
		Parent(nullptr);
	}

	mCurrentState = Dead;
}

bool Enemy::InDeathAnimation() {
	return mDeathAnimation->IsAnimating();
}