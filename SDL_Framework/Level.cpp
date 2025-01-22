#include "Level.h"

void Level::StartStage() {
	mStageStarted = true;
}

Level::Level(int stage, PlaySideBar* sideBar, Player* player){

	mTimer = Timer::Instance();
	mSideBar = sideBar;
	mSideBar->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	mStageLabel = new GLTexture("STAGE", "emulogic.ttf", 20, { 0, 255, 0 });
	mStageLabel->Parent(this);
	mStageLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);

	mStageNumber = new Scoreboard({ 0, 255, 0});
	mStageNumber->Score(stage);
	mStageNumber->Parent(this);
	mStageNumber->Position(Graphics::SCREEN_WIDTH * 0.56f, Graphics::SCREEN_HEIGHT * 0.6f);

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new GLTexture("READY", "emulogic.ttf", 32, { 150, 0,0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.6f);

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mPlayerHit = false;
	mRespawnDelay = 3.0f;
	mRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new GLTexture("GAME OVER!!", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = Running;

	mCrabCount = 0;
	mOctopusCount = 0;
	mSquidCount = 0;
	mShipCount = 0;

	std::string fullPath = SDL_GetBasePath();

	if (mStage == 1) {
		fullPath.append("Data/Level1.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		if (mSpawningFinished) {
			mSpawningPatterns.Clear();
		}
	}

	if (mStage == 2) {	
		fullPath.append("Data/Level2.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}
		
	if (mStage == 3) {
		fullPath.append("Data/Level3.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}

	if (mStage == 4) {
		fullPath.append("Data/Challenge.xml");
		mSpawningPatterns.LoadFile(fullPath.c_str());
		std::cout << mStage << std::endl;
	}

	mChallengeStage = mSpawningPatterns.FirstChildElement("Level")
		->FirstChildElement()
		->BoolAttribute("value");

	if (!mChallengeStage) {
		mFormation = new Formation();
		mFormation->Position(Graphics::SCREEN_WIDTH * 0.5f, 355.0f);
		Enemy::SetFormation(mFormation);
	
		for (int i = 0; i < MAX_CRABS; i++) {
			mFormationCrabs[i] = nullptr;
		}
	
		for (int i = 0; i < MAX_OCTOPI; i++) {
			mFormationOctopi[i] = nullptr;
		}
	
		for (int i = 0; i < MAX_SQUIDS; i++) {
			mFormationSquids[i] = nullptr;
		}

		for (int i = 0; i < MAX_SHIPS; i++) {
			mFormationShip[i] = nullptr;
		}
	}
	
	mCurrentFlyInPriority = 0;
	mCurrentFlyInIndex = 0;
	mSpawnDelay = 0.2f;
	mSpawnTimer = 0.0f;
	mSpawningFinished = false;

	mDivingCrab = nullptr;
	mSkipFirstCrab = false;
	mCrabDiveDelay = 1.0f;
	mCrabDiveTimer = 0.0f;

	mDivingOctopus = nullptr;
	mDivingOctopus2 = nullptr;
	mOctopusDiveDelay = 3.0f;
	mOctopusDiveTimer = 0.0f;

	mDivingSquid = nullptr;
	mCaptureDive = true;
	mSkipFirstSquid = true;
	mSquidDiveDelay = 5.0f;
	mSquidDiveTimer = 0.0f;

	mDivingShip = nullptr;
	mSkipFirstShip = false;
	mShipDiveDelay = 6.0f;
	mShipDiveTimer = 0.0f;

	Enemy::CurrentPlayer(mPlayer);
}

Level::~Level() {
	mTimer = nullptr;
	mSideBar = nullptr;
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

	for (int i = 0; i < MAX_CRABS; i++) {
		delete mFormationCrabs[i];
		mFormationCrabs[i] = nullptr;
	}
	
	for (int i = 0; i < MAX_OCTOPI; i++) {
		delete mFormationOctopi[i];
		mFormationOctopi[i] = nullptr;
	}
	
	for (int i = 0; i < MAX_SQUIDS; i++) {
		delete mFormationSquids[i];
		mFormationSquids[i] = nullptr;
	}

	for (int i = 0; i < MAX_SHIPS; i++) {
		delete mFormationShip[i];
		mFormationShip[i] = nullptr;
	}

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
		mPlayer->Active(true);
		mPlayer->SetVisible(true);

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
		if (mPlayer->WasHit()) {
			mSideBar->SetTanks(mPlayer->Lives());

			mPlayerHit = true;
			mRespawnTimer = 0.0f;
			mPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mRespawnTimer == 0.0f) {
				mPlayer->SetVisible(false);
			}
			mRespawnTimer += mTimer->DeltaTime();
			if (mRespawnTimer >= mRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->SetVisible(true);
				mPlayerHit = false;
			}
		}
		else {
			if (mGameOverTimer == 0.0f) {
				mPlayer->SetVisible(false);
			}
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = GameOver;
			}
		}
	}
}

void Level::HandleEnemySpawning() {

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S) &&
		mCrabCount < MAX_CRABS) {
		mEnemies.push_back(new Crab(mCrabCount++, false));
		//mButterflyCount++;
	}

	//mSpawnTimer += mTimer->DeltaTime();

	//if (mSpawnTimer >= mSpawnDelay) {
	//	XMLElement* element = mSpawningPatterns.FirstChildElement("Level")
	//		->FirstChild()->NextSiblingElement();
	//	bool spawned = false;
	//	bool priorityFound = false;

	//	while (element != nullptr) {
	//		int priority = element->IntAttribute("priority");

	//		if (mCurrentFlyInPriority == priority) {
	//			priorityFound = true;
	//			int path = element->IntAttribute("path");
	//			XMLElement* child = element->FirstChildElement();

	//			for (int i = 0; i < mCurrentFlyInIndex && child != nullptr; i++) {
	//				child = child->NextSiblingElement();
	//			}

	//			if (child != nullptr) {
	//				std::string type = child->Attribute("type");
	//				int index = child->IntAttribute("index");

	//			     if (type.compare("Crab") == 0) {
	//					if (!mChallengeStage) {
	//						
	//						mFormationCrabs[index] = new Crab(index, false);
	//						mCrabCount += 1;
	//					}
	//					else {
	//						//TODO: Change the challenge boolean to true once Challenge logic is implemented
	//						mEnemies.push_back(new Crab(index, false));
	//					}
	//				}
	//				else if (type.compare("Octopus") == 0) {
	//					if (!mChallengeStage) {
	//						mFormationOctopi[index] = new Octopus(index, false);
	//						mOctopusCount ++;
	//					}
	//					else {
	//						mEnemies.push_back(new Octopus(index,false));
	//					}
	//				}
	//				else if (type.compare("Squid") == 0) {
	//					if (!mChallengeStage) {
	//						mFormationSquids[index] = new Squid(index, false);
	//						mSquidCount ++;
	//					}
	//					else {
	//						mEnemies.push_back(new Squid(index, false));
	//					}
	//				}

	//				else if (type.compare("RedShip") == 0) {
	//					 if (!mChallengeStage) {
	//						 mFormationShip[index] = new RedShip(index, false);
	//						 mShipCount++;
	//					 }
	//					 else {
	//						 mEnemies.push_back(new RedShip(index, false));
	//					 }
	//				 }

	//				spawned = true;
	//			}
	//		}

	//		element = element->NextSiblingElement();
	//	}

	//	if (!priorityFound) {

	//		mSpawningFinished = true;
	//	}
	//	else {
	//		if (!spawned) {

	//			if (!EnemyFlyingIn()) {
	//				mCurrentFlyInPriority += 1;
	//				mCurrentFlyInIndex = 0;
	//			}
	//		}
	//		else {
	//			mCurrentFlyInIndex += 1;
	//		}
	//	}

	//	mSpawnTimer = 0.0f;
	//}
}

bool Level::EnemyFlyingIn() {
	for (Crab* crab : mFormationCrabs) {
		if (crab != nullptr &&
			crab->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Octopus* octopus : mFormationOctopi) {
		if (octopus != nullptr &&
			octopus->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (Squid* squid : mFormationSquids) {
		if (squid != nullptr &&
			squid->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	for (RedShip* redShip : mFormationShip) {
		if (redShip != nullptr &&
			redShip->CurrentState() == Enemy::FlyIn) {
			return true;
		}
	}

	return false;
}


void Level::HandleEnemyFormation() {
	mFormation->Update();

	bool levelCleared = mSpawningFinished;

	for (Crab* crab : mFormationCrabs) {
		if (crab != nullptr) {
			crab->Update();

			if (crab->CurrentState() != Enemy::Dead ||
				crab->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Octopus* octopus : mFormationOctopi) {
		if (octopus != nullptr) {
			octopus->Update();

			if (octopus->CurrentState() != Enemy::Dead ||
				octopus->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (RedShip* redShip : mFormationShip) {
		if (redShip != nullptr) {
			redShip->Update();

			if (redShip->CurrentState() != Enemy::Dead ||
				redShip->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	for (Squid* squid : mFormationSquids) {
		if (squid != nullptr) {
			squid->Update();

			if (squid->CurrentState() != Enemy::Dead ||
				squid->InDeathAnimation()) {
				levelCleared = false;
			}
		}
	}

	if (!mFormation->Locked()) {
		if (mCrabCount == MAX_CRABS &&
			mOctopusCount == MAX_OCTOPI &&
			mSquidCount == MAX_SQUIDS && 
			mShipCount == MAX_SHIPS){
			if (!EnemyFlyingIn()) {
				mFormation->Lock();
			}
		}
	}
	//else {
	//	HandleEnemyDiving();
	//}

	if (levelCleared) {
		mCurrentState = Finished;
	}
}

//void Level::HandleEnemyDiving() {
//
//	if (mDivingCrab == nullptr) {
//		mCrabDiveTimer += mTimer->DeltaTime();
//
//		if (mCrabDiveTimer >= mCrabDiveDelay) {
//			bool skipped = false;
//
//			for (int i = MAX_CRABS - 1; i >= 0; i--) {
//				if (mFormationCrabs[i] != nullptr
//					&& mFormationCrabs[i]->CurrentState() == Enemy::InFormation) {
//					if (!mSkipFirstCrab || (mSkipFirstCrab && skipped)) {
//						mDivingCrab = mFormationCrabs[i];
//						mDivingCrab->Dive();
//						mSkipFirstCrab = !mSkipFirstCrab;
//						break;
//					}
//				}
//				skipped = true;
//			}
//
//			mCrabDiveTimer = 0.0f;
//		}
//	}
//	else {
//		if (mDivingCrab->CurrentState() != Enemy::Diving) {
//			mDivingCrab = nullptr;
//		}
//	}
//
//	mOctopusDiveTimer += mTimer->DeltaTime();
//	if (mOctopusDiveTimer >= mOctopusDiveDelay) {
//		for (int i = MAX_OCTOPI - 1; i >= 0; i--) {
//			if (mFormationOctopi[i]->CurrentState() == Enemy::InFormation) {
//				if (mDivingOctopus == nullptr) {
//					mDivingOctopus = mFormationOctopi[i];
//					mDivingOctopus->Dive();
//				}
//				else if (mDivingOctopus2 == nullptr) {
//					mDivingOctopus2 = mFormationOctopi[i];
//					mDivingOctopus2->Dive();
//				}
//				break;
//			}
//		}
//
//		mOctopusDiveTimer = 0.0f;
//	}
//
//	if (mDivingOctopus != nullptr && mDivingOctopus->CurrentState() != Enemy::Diving) {
//		mDivingOctopus = nullptr;
//	}
//	if (mDivingOctopus2 != nullptr && mDivingOctopus2->CurrentState() != Enemy::Diving) {
//		mDivingOctopus2 = nullptr;
//	}
//
//	if (mDivingShip == nullptr) {
//		mShipDiveTimer += mTimer->DeltaTime();
//
//		if (mShipDiveTimer >= mShipDiveDelay) {
//			bool skipped = false;
//
//			for (int i = MAX_SHIPS - 1; i >= 0; i--) {
//				if (mFormationShip[i] != nullptr
//					&& mFormationShip[i]->CurrentState() == Enemy::InFormation) {
//					if (!mSkipFirstShip || (mSkipFirstShip && skipped)) {
//						mDivingShip = mFormationShip[i];
//						mDivingShip->Dive();
//						mSkipFirstShip = !mSkipFirstShip;
//						break;
//					}
//				}
//				skipped = true;
//			}
//
//			mShipDiveTimer = 0.0f;
//		}
//	}
//	else {
//		if (mDivingShip->CurrentState() != Enemy::Diving) {
//			mDivingShip = nullptr;
//		}
//	}
//
//	if (mDivingSquid == nullptr) {
//		mSquidDiveTimer += mTimer->DeltaTime();
//
//		if (mSquidDiveTimer >= mSquidDiveDelay) {
//			bool skipped = false;
//			for (int i = MAX_SQUIDS - 1; i >= 0; i--) {
//				if (mFormationSquids[i]->CurrentState() == Enemy::InFormation) {
//					if (!mSkipFirstSquid || (mSkipFirstSquid && skipped)) {
//						mDivingSquid = mFormationSquids[i];
//						if (mCaptureDive) {
//							mDivingSquid->Dive(1);
//						}
//						else {
//							mDivingSquid->Dive();
//							int index = mDivingSquid->Index();
//							int firstEscortIndex = (index % 2 == 0) ? (index * 2) : (index * 2 - 1);
//							int secondEscortIndex = firstEscortIndex + 4;
//
//							int thirdEscortIndex = -1;			//RedShip Escort 
//							
//							if (mFormationShip[i] != nullptr) {
//								thirdEscortIndex = mDivingSquid->Index();	// have RedShip associated with captureboss by index
//							}
//
//							if (mFormationCrabs[firstEscortIndex]->CurrentState() == Enemy::InFormation) {
//								mFormationCrabs[firstEscortIndex]->Dive(1);
//							}
//							if (mFormationCrabs[secondEscortIndex]->CurrentState() == Enemy::InFormation) {
//								mFormationCrabs[secondEscortIndex]->Dive(1);
//							}
//							if (thirdEscortIndex != -1 && mFormationShip[thirdEscortIndex]->CurrentState() == Enemy::InFormation) {
//								mFormationShip[thirdEscortIndex]->Dive(1);
//							}
//						}
//						mSkipFirstSquid = !mSkipFirstSquid;
//						mCaptureDive = !mCaptureDive;
//						break;
//					}
//					skipped = true;
//				}
//			}
//
//			mSquidDiveTimer = 0.0f;
//		}
//	}
//	else {
//		if (mDivingSquid->CurrentState() != Enemy::Diving) {
//			mDivingSquid = nullptr;
//		}
//	}
//}

void Level::Update() {
	if (!mStageStarted) {
		HandleStartLabels();
	}
	else {

		if (!mSpawningFinished) {
			HandleEnemySpawning();
		}

		if (!mChallengeStage) {
			HandleEnemyFormation();
		}
		else {
			for (auto enemy : mEnemies) {
				enemy->Update();
			}
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
		if (!mChallengeStage) {
			for (Crab* crab : mFormationCrabs) {
				if (crab != nullptr) {
					crab->Render();
				}
			}

			for (Octopus* octopus : mFormationOctopi) {
				if (octopus != nullptr) {
					octopus->Render();
				}
			}

			for (RedShip* redShip : mFormationShip) {
				if (redShip != nullptr) {
					redShip->Render();
				}
			}

			for (Squid* squid : mFormationSquids) {
				if (squid != nullptr) {
					squid->Render();
				}
			}

		}

		else {
			for (auto enemy : mEnemies) {
				enemy->Render();
			}
		}

		if (mPlayerHit) {
			if (mRespawnTimer >= mRespawnLabelOnScreen) {
				mReadyLabel->Render();
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen) {
				mGameOverLabel->Render();
			}
		}
	}
}