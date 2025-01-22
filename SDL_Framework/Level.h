#pragma once
#include "PlaySideBar.h"
#include "Player.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"
#include "RedShip.h"
#include "Tinyxml2.h"

using namespace SDL_Framework;
using namespace tinyxml2;

class Level : public GameEntity {

public:
	enum LevelStates {Running, Finished, GameOver};

	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	LevelStates State();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	Player* mPlayer;
	Formation* mFormation;

	static const int MAX_CRABS = 22;
	static const int MAX_OCTOPI = 22;
	static const int MAX_SQUIDS = 11;
	static const int MAX_SHIPS = 4;

	int mCrabCount;
	int mOctopusCount;
	int mSquidCount;
	int mShipCount;

	Crab* mFormationCrabs[MAX_CRABS];
	Octopus* mFormationOctopi[MAX_OCTOPI];
	Squid* mFormationSquids[MAX_SQUIDS];
	RedShip* mFormationShip[MAX_SHIPS];

	Crab* mDivingCrab;
	bool mSkipFirstCrab;
	float mCrabDiveDelay;
	float mCrabDiveTimer;

	Octopus* mDivingOctopus;
	Octopus* mDivingOctopus2;
	float mOctopusDiveDelay;
	float mOctopusDiveTimer;

	Squid* mDivingSquid;
	bool mCaptureDive;
	bool mSkipFirstSquid;
	float mSquidDiveDelay;
	float mSquidDiveTimer;

	RedShip* mDivingShip;
	bool mSkipFirstShip;
	float mShipDiveDelay;
	float mShipDiveTimer;
	bool mShipSpawn;

	std::vector<Enemy*> mEnemies;	//debug testing

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	float mSpawnDelay;
	float mSpawnTimer;
	bool mSpawningFinished;

	int mStage; 
	bool mChallengeStage;
	bool mStageStarted;

	Texture* mReadyLabel;
	Scoreboard* mStageNumber;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	
	void StartStage();

	bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	//void HandleEnemyDiving();
};