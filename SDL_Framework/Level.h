#pragma once
#include "PlaySideBar.h"
#include "BackgroundStar.h"

using namespace SDL_Framework;

class Level : public GameEntity {

public:
	Level(int stage, PlaySideBar* sideBar);
	~Level();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mBackgroundStars;

	int mStage; 
	bool mStageStarted;

	Texture* mReadyLabel;
	Scoreboard* mStageNumber;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	void StartStage();
};