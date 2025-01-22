#pragma once
#include "Level.h"
#include "Player.h"

using namespace SDL_Framework;

class PlayScreen : public GameEntity {

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextLevel();

	bool GameOver();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	AudioManager* mAudio;

	PlaySideBar* mSideBar;

	Player* mPlayer;

	Texture* mStartLabel;

	Level* mLevel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;
	bool mLevelStarted;
	int mCurrentStage;
};