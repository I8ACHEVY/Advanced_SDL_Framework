#pragma once
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

using namespace SDL_Framework;

class PlaySideBar : public GameEntity {
public:
	PlaySideBar();
	~PlaySideBar();

	void SetTanks(int tanks);
	void SetPlayerScore(int score);
	void SetHighScore(int score);

	void SetLevel(int level);

	void Update() override;
	void Render() override;

private:
	static const int MAX_TANK_TEXTURES = 5;

	Timer* mTimer;
	AudioManager* mAudio;

	Texture* mTopBackground;
	Texture* mBottomBackground;

	Texture* mHighLabel;
	Texture* mP1ScoreLabel;
	Texture* mP2ScoreLabel;
	Scoreboard* mHighScoreBoard;

	Texture* mOneUpLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mOneUpLabelVisible;

	Scoreboard* mPlayer1Score;
	Scoreboard* mPlayer2Score;

	GameEntity* mTanks;
	Texture* mTankTextures[MAX_TANK_TEXTURES];
	Scoreboard* mTotalTanksLabel;

	int mTotalTanks;

	GameEntity* mFlags;
	std::vector<Texture*> mFlagTextures;
	int mRemainingLevels;

	float mFlagXOffset;
	float mFlagYOffset;
	float mFlagTimer;
	float mFlagInterval;

	void ClearFlags();
	void AddNextFlag();
	void AddFlag(std::string filename, float width, int value);
};