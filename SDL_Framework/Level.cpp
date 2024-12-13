#include "Level.h"

void Level::StartStage() {
	mStageStarted = true;
}

Level::Level(int stage, PlaySideBar* sideBar, Player* player) {
	mTimer = Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(stage);
	mBackgroundStars = BackgroundStars::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new Texture("STAGE", "emulogic.ttf", 20, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageNumber = new Scoreboard({ 75, 75, 200 });
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH * 0.56f, Graphics::SCREEN_HEIGHT * 0.5f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, { 150, 0,0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER!!", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = Running;

	mFormation = new Formation();
	mFormation->Position(Graphics::SCREEN_WIDTH * 0.5f, 355.0f);	//150.0f
	Enemy::SetFormation(mFormation);

	mButterflyCount = 0;
	mWaspCount = 0;
	mBossCount = 0;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Data/Level1.xml");
	mSpawningPatterns.LoadFile(fullPath.c_str());

	mChallengeStage = mSpawningPatterns.FirstChildElement("Level")
		->FirstChildElement()
		->BoolAttribute("value");

	//if (!mChallengeStage) {
	//	mFormation = new Formation();
	//	mFormation->Position(Graphics::SCREEN_WIDTH * 0.4f, 150.0f);
	//	Enemy::SetFormation(mFormation);

	//	for (int i = 0; i < MAX_BUTTERFDLIES; i++) {
	//		mFormationButterflies[i = nullptr; ]
	//	}

	//	for (int i = 0; i < MAX_Wasps; i++) {
	//		mFormationWasps[i = nullptr;]
	//	}

	//	for (int i = 0; i < MAX_Bosses; i++) {
	//		mFormationBosses[i = nullptr;]
	//	}
	//}

	//mCurrentFlyInPriority = 0;
	//mCurrentFlyInIndex = 0;
	//m
}

Level::~Level() {
	mTimer = nullptr;
	mSideBar = nullptr;
	mBackgroundStars = nullptr;
	mPlayer = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;

	delete mStageNumber;
	mStageNumber = nullptr;

	delete mReadyLabel;
	mReadyLabel;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	delete mFormation;
	mFormation = nullptr;

	//for (int i = 0; i < MAX_BUTTERFLIES; i++) {
	//	delete mFormationButterflies[i];
	//	mFormationButterflies[i] = nullptr;
	//}

	//for (int i = 0; i < MAX_WASPS; i++) {
	//	delete mFormationWasps[i];
	//	mFormationWasps][i] = nullptr;
	//}

	//for (int i = 0; i < MAX_BUTTERFLIES; i++) {
	//	delete mFormationButterflies[i];
	//	mFormationButterflies][i] = nullptr;
	//}

	for (auto enemy : mEnemies) {
		delete enemy;
		enemy = nullptr;
	}

	mEnemies.clear();
}

Level::LevelStates Level::State() {
	return mCurrentState;
}

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();

	if (mLabelTimer >= mStageLabelOffScreen) {
		mBackgroundStars->Scroll(true);
		mPlayer->Active(true);
		mPlayer->Visible(true);

		if (mStage > 1) {
			StartStage();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {
				StartStage();
			}
		}
	}
}

void Level::HandleCollisions() {
	if (!mPlayerHit) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {	//Testing
			mPlayer->WasHit();
			mSideBar->SetShips(mPlayer->Lives());

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			mPlayer->Active(false);
			mBackgroundStars->Scroll(false);
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				mPlayer->Visible(false);
			}
			mRespawnTimer += mTimer->DeltaTime();
			if (mRespawnTimer >= mRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mBackgroundStars->Scroll(true);
			}
		}
		else {
			if (mGameOverTimer == 0.0f) {
				mPlayer->Visible(false);
			}
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning() {//missed class edited
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S) &&		//Testing
		mButterflyCount < MAX_BUTTERFLIES) {

		mEnemies.push_back(new Butterfly(0, mButterflyCount, false));
		mButterflyCount++;
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W) &&		//Testing
		mWaspCount < MAX_WASPS) {

		mEnemies.push_back(new Wasp(0, mWaspCount++, false, false));
		//mWaspCount++;
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F) &&		//Testing
		mBossCount < MAX_BOSSES) {

		mEnemies.push_back(new Boss(0, mBossCount++, false));
		//mBossCount++;
	}
}

void Level::HandleEnemyFormation() {
	mFormation->Update();

	if (mButterflyCount == MAX_BUTTERFLIES &&
		mWaspCount == MAX_WASPS &&
		mBossCount == MAX_BOSSES) {

		bool flyIn = false;
		for (auto enemy : mEnemies) {
			if (enemy->CurrentState() == Enemy::FlyIn) {
				flyIn = true;
				break;
			}
		}

		if (!flyIn) {
			mFormation->Lock();
		}
	}
}

void Level::HandleEnemyDiving() {
	if (mFormation->Locked()) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_V)) {		//Testing
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Wasp &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_B)) {		//Testing
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Butterfly &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();
					break;
				}
			}
		}

		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_G)) {		//Testing
			for (auto enemy : mEnemies) {
				if (enemy->Type() == Enemy::Boss &&
					enemy->CurrentState() == Enemy::InFormation) {
					enemy->Dive();

					int index = enemy->Index();
					int firstEscortIndex = (index % 2 == 0) ?
						(index * 2) : (index * 2 - 1);
					int secondEscortIndex = firstEscortIndex + 4;

					for (auto butterfly : mEnemies) {
						//verify the enemy is a butterfly in formation &
						//the butterfly has either the first or second escort index
						if (butterfly->Type() != Enemy::Butterfly) { continue; }
						if (butterfly->CurrentState() != Enemy::InFormation) { continue;}

						if (butterfly->Index() == firstEscortIndex ||
							butterfly->Index() == secondEscortIndex){
							butterfly->Dive(1);
						}
						// or do this
						//if (butterfly->Type() == Enemy::Butterfly &&
						//	butterfly->CurrentState() == Enemy::InFormation) {
						// 
						//	if (butterfly->Index() == firstEscortIndex || 
						//	    butterfly->Index() == secondEscortIndex) {
						//		
						//		butterfly->Dive(1);
						//	}
						//}
					}

					break;
				}
			}
		}
	}
}

void Level::Update() {
	if (!mStageStarted) {
		HandleStartLabels();
	}
	else {
		HandleEnemySpawning();	//missed
		HandleEnemyFormation();
		HandleEnemyDiving();

		for (auto enemy : mEnemies) {
			enemy->Update();
		}

		HandleCollisions();

		if (mPlayerHit) {
			HandlePlayerDeath();
		}
		else {
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {		//Testing
				mCurrentState = Finished;
			}
		}
	}
}

void Level::Render() {
	if (!mStageStarted) {
		if (mLabelTimer > mStageLabelOnScreen &&
			mLabelTimer < mStageLabelOffScreen) {

			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}
	else {
		for (auto enemy : mEnemies) {
			enemy->Render();
		}

		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				mReadyLabel->Render();
			}
			
			if (mGameOverTimer >= mGameOverLabelOnScreen){
				mGameOverLabel->Render();
			}
		}
	}
}